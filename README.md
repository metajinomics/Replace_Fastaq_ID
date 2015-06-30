# Replace_Fastaq_ID
This program let you add file name after FASTQ-ID

To make fileID.txt

'''
grep ^"@G" *.fastq > fileID.txt
'''

Merge fastq files into one

'''
cat *.fastq > test.fastq
'''

Replace ID name

'''
g++ ReplaceNameFastq.cpp -o ReplaceNameFastq

./ReplaceNameFastq test.fastq fileID.txt NewID.fastq
'''


