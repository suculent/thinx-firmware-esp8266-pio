Import("env")

from subprocess import call

#
# Dump build environment (for debug)
#
#

# Version tagging action

def before_build(source, target, env):
    call(["SET", "PLATFORMIO_BUILD_FLAGS=\"-DTHX_REVISION=$(git describe --abbrev=4 --dirty --always --tags)\""])
    print "extra_script.py action > before_build"
    print env.Dump()
    print "Current build targets", map(str, BUILD_TARGETS)

env.AddPreAction("buildprog", before_build)
