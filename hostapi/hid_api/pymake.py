################################################################################################
#   Name: pymake.py                                                                            #
#                                                                                              #
#   Author: Alexandr Limanec (TyTDobby)                                                        #
#                                                                                              #
#   Version: 0.1                                                                               #
#                                                                                              #
#   Description: Script for build project C/C++ and maybe other programming language.          #
#                Build support on Linux and Windows.                                           #
#                                                                                              #
################################################################################################
import os    
import sys
import json

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def count(dir, counter=0):
    "returns number of files in dir and subdirs"
    for pack in os.walk(dir):
        for f in pack[2]:
            counter += 1
    return dir + " : " + str(counter) + " files"
################################################
# Name: buildInWindows                         #
# Description: build project in linux          #
# Arguments:                                   #
#            src - list source file            #
#            obj - list object file            #
#            flag - flags for compile program  #
# Returns: none                                #
################################################
def buildInLinux(src, obj, linkObjs, flag, compiler):
    cnt = 0
    while cnt < len(src):
        print(bcolors.OKBLUE + ' CC ' + bcolors.ENDC + src[cnt])
        os.system(compiler + ' ' + flag + ' -c ' + src[cnt] + ' -o ' + obj[cnt])
        cnt += 1
    print(bcolors.OKBLUE + ' Creating an executable file: ' + bcolors.ENDC + build + 'bin/' + namePro)
    sObj = ' ' + linkObjs[0]
    cnt = 1
    while cnt < len(linkObjs):
        sObj += ' ' + linkObjs[cnt]
        cnt += 1
    os.system(compiler + ' ' + flag + " -o " + build + 'bin/' + namePro + ' ' + sObj)
        # print(bcolors.OKGREEN + " Success!" + bcolors.ENDC)
################################################
# Name: buildInWindows                         #
# Description: build project in windows        #
# Arguments:                                   #
#            src - list source file            #
#            obj - list object file            #
#            flag - flags for compile program  #
# Returns: none                                #
################################################
def buildInWindows(src, obj, flag):
    cnt = 0
    while cnt < len(src):
        print(bcolors.OKBLUE + " CC " + bcolors.ENDC + src[cnt])
        os.system("gcc " + flag + " -c " + src[cnt] + " -o " + obj[cnt])
        cnt += 1
    print(bcolors.OKBLUE + " Creating an executable file: " + bcolors.ENDC + build + "bin\\" + namePro)
    sObj = " " + obj[0]
    cnt = 1
    while cnt < len(obj):
        sObj += " " + obj[cnt]
        cnt += 1
    os.system("gcc " + flag + " -o " + build + "bin\\" + namePro + " " + sObj)
        # print(bcolors.OKGREEN + " Success!" + bcolors.ENDC)
################################################
# Name: get_filepaths                          #
# Description: search all files                #
# Arguments:                                   #
#           directory - path to directory      #
# Returns: list files                          #
################################################
def get_filepaths(directory):
    """
    This function will generate the file names in a directory 
    tree by walking the tree either top-down or bottom-up. For each 
    directory in the tree rooted at directory top (including top itself), 
    it yields a 3-tuple (dirpath, dirnames, filenames).
    """
    file_paths = []  # List which will store all of the full filepaths.

    # Walk the tree.
    for root, directories, files in os.walk(directory):
        for filename in files:
            # Join the two strings in order to form the full filepath.
            filepath = os.path.join(root, filename)
            file_paths.append(filepath)  # Add it to the list.

    return file_paths  # Self-explanatory.
################################################
# Name: getNameFile                            #
# Description: select name file                #
# Arguments:                                   #
#           pathFile - path to file            #
# Returns: name file                           #
################################################
def getNameFile(pathFile):
    out = []
    if osBuild == 'linux':
        out = pathFile.split('/')
        return out[len(out) - 1]
    elif osBuild == 'windows':
        out = pathFile.split('\\')
        return out[len(out) - 1]

def testSrc(src, obj):
    cnt = 0
    temp = []
    while cnt < len(obj):
        if os.access(obj[cnt], os.F_OK):
            if os.path.getmtime(obj[cnt]) < os.path.getmtime(src[cnt]):
                print(os.path.getmtime(obj[cnt]))
                print(os.path.getmtime(src[cnt]))
                temp.append(src[cnt])
        cnt += 1
    return temp



def deleteSpace(val):
    cnt = 0
    strLen = len(val)
    strOut = ''
    while cnt < strLen:
        if val[cnt] != ' ':
            strOut += val[cnt]

        cnt += 1
    return strOut


build = 0
namePro = 0
flags = 0
osBuild = 0
config = 'config.json'
extensionFiles = 0
compil = 0
run = False
buildProject = False
win = False
clean = False
source = []
header = []
objects = []
tempSrc = []
tempObj = []
linkObj = []
i = 0
if len(sys.argv) > 1:
    while i < len(sys.argv):
        if sys.argv[i] == '-l':
            osBuild = 'linux'
        elif sys.argv[i] == '-w':
            osBuild = 'windows'
        elif sys.argv[i] == '-r':
            run = True
        elif sys.argv[i] == '-b':
            buildProject = True
        elif sys.argv[i] == '-c':
            clean = True
        i += 1
elif len(sys.argv) == 1:
    print('\tError! No arguments!\n'
          'Example build on linux: \n'
          '\t\'python pymake.py -l -b\'\n'
          'Example build on windows: \n'
          '\t\'python pymake.py -w -b\'\n')
    sys.exit()

if os.path.isfile(config):
    f = open(config, 'r')
    readJson = f.read()
    data = json.loads(readJson)
    for i in data['config'][osBuild]:
        namePro = i['name']
        build = i['build_dir'] + '/'
        flags = i['flags']
        extensionFiles = i['extensionFiles']
        compil = i['compiler']

# Run the above function and store its results in a variable.   
pathFile = get_filepaths(os.getcwd())

listExt = extensionFiles.split('|')
if clean:
    os.system('rm -r ' + build)
if buildProject:

    i = 0
    while i < len(pathFile):
        pathFile[i] = pathFile[i].replace(os.getcwd() + '/', '')
        if pathFile[i].endswith(listExt[0]):
            tempSrc.append(pathFile[i])
            tempObj.append(build + "obj/" + getNameFile(pathFile[i].replace(listExt[0], '.o')))
        if pathFile[i].endswith(listExt[1]):
            header.append(pathFile[i])
        i += 1

    i = 0
    while i < len(tempSrc):
        if os.access(tempObj[i], os.F_OK):
            statbuf = os.stat(tempObj[i])
            if os.path.getmtime(tempObj[i]) < os.path.getmtime(tempSrc[i]):
                objects.append(tempObj[i])
                source.append(tempSrc[i])
        else:
            objects.append(tempObj[i])
            source.append(tempSrc[i])
        
        i += 1

    if len(objects) != 0:
        if osBuild == 'linux':
            if not os.path.exists(build):
                os.mkdir(build)
            if not os.path.exists(build + "bin/"):
                os.mkdir(build + "bin/")
            if not os.path.exists(build + "obj/"):
                os.mkdir(build + "obj/")
            buildInLinux(source, objects, tempObj, flags, compil)
        elif osBuild == 'windows':
            if not os.path.exists(build):
                os.mkdir(build)
            if not os.path.exists(build + "bin\\"):
                os.mkdir(build + "bin\\")
            if not os.path.exists(build + "obj\\"):
                os.mkdir(build + "obj\\")
            buildInWindows(source, objects, flags)
    else:
        print('\t**** No changes! ****')

if run:
    if osBuild == 'linux':
        print(bcolors.OKBLUE + " Run: " + bcolors.ENDC + build + "bin/" + namePro)
        os.system('./' + build + "bin/" + namePro)
    elif osBuild == 'windows':
        print(bcolors.OKBLUE + " Run: " + bcolors.ENDC + build + "bin\\" + namePro + '\n')
        os.system(build + "bin\\" + namePro)

