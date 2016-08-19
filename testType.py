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
runTest( 9, "on line number 39, error: trying to assign to a const type\n" )
runTest( 10, "on line number 22, error: undefined variable\n" )
runTest( 11, "on line number 16, error: wrong length or wrong type in one dimension array assign\n" )
runTest( 12, "on line number 3, error: wrong length or wrong type in two dimensions array assign\n" )
runTest( 13, "on line number 3, error: wrong length or wrong type in one dimension array assign\n" )
runTest( 14, "on line number 3, error: trying to init a list contains differetn types\n" )
runTest( 15, "on line number 5, error: type of expr and var do not match in assignment\n" )
runTest( 16, "on line number 4, error: trying to assign to a const type\n" )
runTest( 17, "on line number 5, error: type of expr and var do not match in assignment\n" )
runTest( 18, "on line number 5, error: Deref can only be applied to integer pointers and char pointers\n" )
runTest( 19, "on line number 5, error: no main\n" )
runTest( 20, "on line number 5, error: main not declare in outermost scope\n" )
runTest( 21, "on line number 4, error: the Main procedure has arguments\n" )
runTest( 22, "on line number 7, error: duplicate procedure names in same scope\n" )
runTest( 23, "on line number 4, error: type mismatch in return statement\n" )
runTest( 24, "on line number 5, error: type mismatch in return statement\n" )
runTest( 25, "on line number 3, error: call to undefined procedure\n" )
print "--------------------------------"
print "         test passed            "
print "--------------------------------"
