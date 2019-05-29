import logging
import argparse
import os
import getpass
import subprocess
import collections
import shutil
import multiprocessing

logger = logging.getLogger("build")
build_targets=['prepare', 'clean', 'distclean', 'make']
map_modules=['framework', 'common', 'controller', 'agent']
dep_modules=['nng', 'safeclib']

class builder(object):
    def __init__(self, name, modules_dir, build_dir, install_dir):
        logger.debug("modules_dir={}, build_dir={}, install_dir={}".format(modules_dir, build_dir, install_dir))

        self.name = name
        self.src_path = "{}/{}".format(modules_dir, name)
        self.build_path = "{}/{}".format(build_dir, name)
        self.install_path = install_dir
        self.env = os.environ.copy()
        self.env["STAGING_DIR"] = ""

    def __str__(self):
        return "'{}' builder configuration:\n\tsrc_path: {}\n\tbuild_path: {}\n\tinstall_path: {}".format(self.name, self.src_path, self.build_path, self.install_path)

    def clean(self):
        if os.path.exists(self.build_path):
            logger.info("cleaning {}".format(self.name))
            shutil.rmtree(self.build_path)

    def distclean(self):
        self.clean()

    def prepare(self):
        pass

    def make(self):
        pass

class cmakebuilder(builder):
    def __init__(self, name, modules_dir, build_dir, install_dir, native_build=False, cmake_verbose=False, make_verbose=False, cmake_flags=[], generator=None):
        self.native_build = native_build
        self.cmake_verbose = cmake_verbose
        self.make_verbose = make_verbose
        self.cmake_flags = cmake_flags
        self.generator = generator

        super(cmakebuilder, self).__init__(name, modules_dir, build_dir, install_dir)

    def clean(self):
        if os.path.exists(self.build_path):
            os.system("xargs rm < {}/install_manifest.txt".format(self.build_path))
        super(cmakebuilder, self).clean()

    def prepare(self):
        if os.path.exists("{}/.prepared".format(self.build_path)):
            logger.info("{} already prepared, skip cmake {}".format(self.build_path, self.name))
            return

        cmd = ["cmake",
               "-H" + self.src_path,
               "-B" + self.build_path,
               "-DSTANDALONE=ON",
               "-DCMAKE_INSTALL_PREFIX=" + self.install_path]
        if not self.native_build:
            cmd.append("-DCMAKE_TOOLCHAIN_FILE=external_toolchain.cmake")
        cmd.extend(['-D%s' %f for f in self.cmake_flags])
        if self.cmake_verbose:
            cmd.append("--debug_output")
        if self.generator:
            cmd.extend(["-G", self.generator])
        logger.info("preparing {}: {}".format(self.name, " ".join(cmd)))
        subprocess.check_call(cmd, env=self.env)
        open("{}/.prepared".format(self.build_path), 'a').close()

    def make(self):
        cmd = ["cmake",
               "--build", self.build_path,
               "--target", "install"]
        if self.make_verbose:
            cmd.extend(["--", "VERBOSE=1"])
        else:
            cmd.extend(["--", "-j", str(multiprocessing.cpu_count() + 1)])
        logger.info("building & installing {}: {}".format(self.name, " ".join(cmd)))
        subprocess.check_call(cmd, env=self.env)

class acbuilder(builder):
    def __init__(self, name, modules_dir, build_dir, install_dir, host_prefix, make_verbose=False):
        self.make_verbose = make_verbose
        self.host_prefix = host_prefix

        super(acbuilder, self).__init__(name, modules_dir, build_dir, install_dir)

    def clean(self):
        if os.path.exists(self.build_path):
            os.system("make -C {} uninstall".format(self.build_path))
        super(acbuilder, self).clean()

    def prepare(self):
        os.chdir(self.src_path)
        cmd = ["./build-tools/autogen.sh"]
        logger.info("preparing {}: {}".format(self.name, " ".join(cmd)))
        subprocess.check_call(cmd, env=self.env)

        self.configure()

    def configure(self):
        os.mkdir(self.build_path)
        os.chdir(self.build_path)
        cmd = [self.src_path + "/configure",
               "--prefix=" + self.install_path]
        if self.host_prefix:
            cmd.append("--host=" + self.host_prefix)
        logger.info("configuring {}: {}".format(self.name, " ".join(cmd)))
        subprocess.check_call(cmd, env=self.env)

    def make(self):
        cmd = ["make", '-C', self.build_path, "install"]
        if self.make_verbose:
            cmd.extend(["V=s"])
        else:
            cmd.extend(["-j", str(multiprocessing.cpu_count() + 1)])
        logger.info("building & installing {}: {}".format(self.name, " ".join(cmd)))
        subprocess.check_call(cmd, env=self.env)

class mapbuild(object):
    def __init__(self, args):
        if args.verbose: logger.setLevel(logging.DEBUG)

        commands = args.commands
        _map_modules = map_modules if 'all' in args.modules or 'map' in args.modules else [m for m in map_modules if m in args.modules]
        _dep_modules = dep_modules if 'all' in args.modules or 'dep' in args.modules else [m for m in dep_modules if m in args.modules]

        logger.info("{} {}".format(commands, _map_modules + _dep_modules))

        # build dep modules
        for name in _dep_modules:
            modules_dir = os.path.join(os.path.realpath(args.map_path), "../3rdparty")
            build_dir = os.path.realpath(modules_dir + '/../multiap/build')
            install_dir = os.path.realpath(build_dir + '/install')

            if name == 'nng':
                args.cmake_flags.append("BUILD_SHARED_LIBS=yes")
                self.builder = cmakebuilder('nng', modules_dir, build_dir, install_dir,
                        args.native, args.cmake_verbose, args.make_verbose, args.cmake_flags, args.generator)

            if name == 'safeclib':
                self.builder = acbuilder('safeclib', modules_dir, build_dir, install_dir,
                        args.host_prefix, args.make_verbose)

            self.run_command(commands)

        # build map modules
        for name in _map_modules:
            modules_dir = os.path.realpath(args.map_path)
            build_dir = os.path.realpath(modules_dir + '/build')
            install_dir = os.path.realpath(build_dir + '/install')

            self.builder = cmakebuilder(name, modules_dir, build_dir, install_dir,
                args.native, args.cmake_verbose, args.make_verbose, args.cmake_flags, args.generator)

            self.run_command(commands)

    def run_command(self, commands):
        logger.debug(self.builder)
        if 'distclean' in commands:
            self.builder.distclean()
        if 'clean' in commands:
            self.builder.clean()
        if 'prepare' in commands:
            self.builder.prepare()
        if 'make' in commands:
            self.builder.prepare()
            self.builder.make()

    @staticmethod
    def configure_parser(parser=argparse.ArgumentParser(prog='build')):
        parser.help = "multiap_sw standalone build module"
        parser.add_argument('modules', choices=['all', 'map', 'dep'] + map_modules + dep_modules, nargs='+', help='module[s] to build')
        parser.add_argument('-c', '--commands', choices=build_targets, nargs='+', default=['make'], help="build command (default is clean+make)")
        parser.add_argument("--verbose", "-v", action="store_true", help="verbosity on")
        parser.add_argument("--native", "-n", action="store_true", help="Build native (not cross compile - ignore external_toolchain.cfg)")
        parser.add_argument("--host-prefix", "-H", help="cross-compile to build programs to run on HOST (only for building safeclib)")
        parser.add_argument('-f', '--cmake-flags', nargs='+', default=[], help="extra cmake flags")
        parser.add_argument("--cmake-verbose", action="store_true", help="cmake verbosity on (pass --debug-output to cmake command)")
        parser.add_argument("--make-verbose", action="store_true", help="make verbosity on (pass VERBOSE=1 to make)")
        parser.add_argument("--generator", "-G", help="Specify a build system generator (cfr. cmake -G)")

        return parser

    def __str__(self):
        return str(self.args)
