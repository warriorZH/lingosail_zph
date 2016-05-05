# -*- coding: UTF-8 -*-

import re
import sys

if __name__ == "__main__":
    if len(sys.argv) == 3:
        in_path = sys.argv[1]
        out_path = sys.argv[2]
        in_fd = open(in_path, 'r')
        out_fd = open(out_path, 'w')
        in_cont = in_fd.readlines()

        pattern = re.compile("\t")
        for in_line in in_cont:
            print in_line
            out_line = pattern.sub('',in_line)
            print out_line
            out_fd.write(out_line)

        in_fd.close()
        out_fd.close()
    else:
        print "input error!"
