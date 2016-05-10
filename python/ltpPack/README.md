#LAT平台优化应用，获取更好的分词效果！！
##文件说明
*rmTab.py
此文件用来将文档中'\t'间隔符去掉，重构成训练数据
调用格式：'python rmTab.py input_path output_path'

*contrast.py
此文件用来进行两种分词结果的对比，并将对比统计结果输出到外部文件
调用格式：'python contrast.py old_result_path new_result_path contrast_result_path'

*ConstructWordList.py
此文件用来将训练数据生成外部词表，供otcws添加外部词表功能测试
调用格式：'python ConstructWordList.py input_path output_path'

