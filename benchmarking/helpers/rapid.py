RAPID_PATH = "<path to rapid executable>"
VAMPIRE_PATH = "<path to vampire executable>"

import os
import sys
import shutil
from easyprocess import EasyProcess

dir_path = os.path.dirname(os.path.realpath(__file__))
RAPID_OUT_PATH = dir_path + "/rapid_o/"

if os.path.exists(RAPID_OUT_PATH):
    shutil.rmtree(RAPID_OUT_PATH)
os.mkdir(RAPID_OUT_PATH)

proc = EasyProcess(("%s -dir %s " % (RAPID_PATH, RAPID_OUT_PATH)) + sys.argv[1]).call()

for file in os.listdir(RAPID_OUT_PATH):
    proc = EasyProcess((VAMPIRE_PATH + " --mode portfolio -sched rapid --input_syntax smtlib2 -t 600 %s" % os.path.join(RAPID_OUT_PATH, file))).call()
    if "SZS status Unsatisfiable for" not in proc.stdout:
        print("UNKNOWN")
        shutil.rmtree(RAPID_OUT_PATH)
        exit(0)
shutil.rmtree(RAPID_OUT_PATH)
print("SAFE")

