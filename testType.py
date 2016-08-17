import subprocess, sys

def checkOutput( expect, real ):
    if ( expect != real ):
        print "***************************"
        print "expect  " + expect
        print "but get " + real
        print "***************************"
        sys.exit(0)

def runTest( number, expect ):
    proc = subprocess.Popen(["./c99-- < typecheckTests/test"+ str(number) +".c",\
                             "/etc/services"], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()

    checkOutput( expect, out )


runTest( 1, "on line number 34, error: type of expr and var do not match in assignment\n")
runTest( 2, "on line number 40, error: return type must not be a pointer type\n")
runTest( 3, "on line number 13, error: trying to assign a value to the array\n")
runTest( 4, "on line number 18, error: incompatible types used in expression\n" )
runTest( 5, "on line number 31, error: undefined variable\n" )
runTest( 6, "on line number 20, error: duplicate variable names in same scope\n" )
runTest( 7, "on line number 47, error: duplicate variable names in same scope\n" )
runTest( 8, "on line number 23, error: trying to switch a non-base type\n" )

print "--------------------------------"
print "         test passed            "
print "--------------------------------"
