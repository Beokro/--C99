
import os
show_errors = True

print "test starts"

cmd = "make"
print "running " + cmd + ":"
os.system(cmd)

print ""

for index in range(24):
    cmd = "./c99-- < tests/test" + str(index) +".c"
    print "running " + cmd + ":"
    os.system(cmd)


cmd = "make clean"
print "running " + cmd + ":"
os.system(cmd)

print ""
