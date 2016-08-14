import subprocess, sys

def checkOutput( expect, real ):
    if ( expect != real ):
        print "***************************"
        print "expect  " + expect
        print "but get " + real
        print "***************************"
        sys.exit(0)


proc = subprocess.Popen(["./c99-- < typecheckTests/test1.c", "/etc/services"], stdout=subprocess.PIPE, shell=True)
(out, err) = proc.communicate()

checkOutput( "on line number 34, error: type of expr and var do not match in assignment\n", out )

print "--------------------------------"
print "         test passed            "
print "--------------------------------"
