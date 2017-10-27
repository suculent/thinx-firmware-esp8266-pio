Import("env")

# Consider possible security implications associated with call module.
# from subprocess import call
from SCons.Script import DefaultEnvironment

# Version tagging action

def before_build(source, target, env):
    env.Append(PLATFORMIO_BUILD_FLAGS=["-DTHX_REVISION=$(git describe --abbrev=4 --dirty --always --tags)"])  # General options that are passed to the C and C++ compilers.

    #call(["SET", "PLATFORMIO_BUILD_FLAGS=\"-DTHX_REVISION=$(git describe --abbrev=4 --dirty --always --tags)\""])

    print "extra_script.py action > before_build"
    print env.Dump()
    print "Current build targets", map(str, BUILD_TARGETS)

env = DefaultEnvironment()
env.AddPreAction("buildprog", before_build)
env.Append(PLATFORMIO_BUILD_FLAGS=["-DTHX_REVISION=$(git describe --abbrev=4 --dirty --always --tags)"])  # General options that are passed to the C and C++ compilers.
print env.Dump()
