# -*- coding: UTF-8 -*-
"""
@filename: contrast.py
@description: contrast two word segment result, and output the result to a file.
                word segment result interval by \t
@author: lingosail-zhangpeihua
@data: 2016-5-5
@log: 1.used for optimize ltp-otcws using
"""
import re
import sys


def contrastNewAndOldSegmentResult(oldResultPath, newResultPath, contrastResultPath):
    """
    :description contrast two word segment result, and output the result to a file.
    :param oldResultPath: segment result of old crf model
    :param newResultPath: segment result of new crf model
    :param contrastResultPath: store the contrast result of new and old segment result
    :return: none
    """
    # open file
    input1_fd = open(oldResultPath, 'r')
    input2_fd = open(newResultPath, 'r')
    output_fd = open(contrastResultPath, 'w')
    # get content
    input1_cont = input1_fd.readlines()
    input2_cont = input2_fd.readlines()
    line_count = 0
    all_file_length = 0
    all_file_diff_length = 0
    for (line1, line2) in zip(input1_cont, input2_cont):
        line_count += 1
        # split lines
        list1 = re.split(r'\t', line1)
        list2 = re.split(r'\t', line2)
        # print list1
        # print list2
        # store all length of lines
        all_len1 = 0
        all_len2 = 0
        line_len_diff = 0
        for item in list1:
            all_len1 += len(item)
        for item in list2:
            all_len2 += len(item)
            all_file_length += (all_len1+all_len2)/2
        # store the current length
        len1 = 0
        len2 = 0
        # store the current search index
        index1 = 0
        index2 = 0
        # store the different condition
        list1_buff = []
        list2_buff = []
        # sign the different condition state start or end
        diff_flag = False
        len1 += len(list1[index1])
        len2 += len(list2[index2])
        if len1 != len2:
            diff_flag = True
            list1_buff.append(list1[index1])
            list2_buff.append(list2[index2])
        while (index1 < len(list1)) & (index2 < len(list2)):
            # print len1,len2
            if len1 < len2:
                # extend lesser list
                index1 += 1
                if index1>=len(list1):
                    output_line = ""
                    for item in list1_buff:
                        output_line += item + '\t'
                        line_len_diff += len(item)
                    output_line += '------\t'
                    for item in list2_buff:
                        output_line += item + '\t'
                    output_fd.write(output_line)
                    output_fd.write('\n')
                    # print output_line
                    diff_flag = False
                    # reset list different condition buff
                    list1_buff = []
                    list2_buff = []
                    all_file_diff_length += line_len_diff
                    output_line = 'line %d percentage %f%%' % (line_count, float(float(line_len_diff) / all_len1)*100)
                    output_fd.write(output_line)
                    output_fd.write('\n')
                    break
                len1 += len(list1[index1])
                list1_buff.append(list1[index1])
                diff_flag = True
            elif len1 > len2:
                # extend lesser list
                index2 += 1
                if index2>=len(list2):
                    output_line = ""
                    for item in list1_buff:
                        output_line += item + '\t'
                        line_len_diff += len(item)
                    output_line += '------\t'
                    for item in list2_buff:
                        output_line += item + '\t'
                    output_fd.write(output_line)
                    output_fd.write('\n')
                    # print output_line
                    diff_flag = False
                    # reset list different condition buff
                    list1_buff = []
                    list2_buff = []
                    all_file_diff_length += line_len_diff
                    output_line = 'line %d percentage %f%%' % (line_count, float(float(line_len_diff) / all_len1)*100)
                    output_fd.write(output_line)
                    output_fd.write('\n')
                    break
                len2 += len(list2[index2])
                list2_buff.append(list2[index2])
                diff_flag = True
            else:
                # correspond word is different
                if diff_flag:  # diff
                    # print "diff"
                    # list1_buff.append(list1[index1])
                    # list2_buff.append(list2[index2])
                    output_line = ""
                    for item in list1_buff:
                        output_line += item + '\t'
                        line_len_diff += len(item)
                    output_line += '------\t'
                    for item in list2_buff:
                        output_line += item + '\t'
                    output_fd.write(output_line)
                    output_fd.write('\n')
                    # print output_line
                    diff_flag = False
                    # reset list different condition buff
                    list1_buff = []
                    list2_buff = []
                    index1 += 1
                    index2 += 1
                    if (index1 < len(list1)) & (index2 < len(list2)):
                        len1 += len(list1[index1])
                        len2 += len(list2[index2])
                        if len1 != len2:
                            diff_flag = True
                            list1_buff.append(list1[index1])
                            list2_buff.append(list2[index2])
                    else:
                        all_file_diff_length += line_len_diff
                        output_line = 'line %d percentage %f%%' % (line_count, float(float(line_len_diff) / all_len1)*100)
                        output_fd.write(output_line)
                        output_fd.write('\n')
                        break
                else:  # normal
                    index1 += 1
                    index2 += 1
                    # print "normal"
                    # print index1,index2
                    # print len(list1),len(list2)
                    if (index1 < len(list1)) & (index2 < len(list2)):
                        len1 += len(list1[index1])
                        len2 += len(list2[index2])
                        if len1 != len2:
                            diff_flag = True
                            list1_buff.append(list1[index1])
                            list2_buff.append(list2[index2])
                    else:
                        all_file_diff_length += line_len_diff
                        output_line = 'line %d percentage %f%%' % (line_count, float(float(line_len_diff) / all_len1)*100)
                        output_fd.write(output_line)
                        output_fd.write('\n')
                        break
    output_line = 'all file changed percentage %f%%' % (float(float(all_file_diff_length) / all_file_length)*100)
    output_fd.write(output_line)
    output_fd.write('\n')
    input1_fd.close()
    input2_fd.close()
    output_fd.close()

if __name__ == "__main__":
    if len(sys.argv) == 4:
        print "start contrasting..."
        # get path
        contrastNewAndOldSegmentResult(sys.argv[1], sys.argv[2], sys.argv[3])
    else:
        print "input example 'python contrast.py new_result_path old_result_path contrast_result_path'"
