/*
 * corpus.cc
 *
 */

#include <cstdio>

#include "corpus.h"

int Corpus::Load(const std::string corpus_file_path) {
	FILE * corpus_file = fopen(corpus_file_path.c_str(), "r");
	if (!corpus_file) {
		fprintf(stderr,
				"%s:%d ERROR: Cannot open corpus file!\n",
				__FILE__,
				__LINE__);
		return -1;
	}
	int read_doc_num = 0;	//已经读取的doc_num
	int doc_id;
	int sent_num, length;

	while (fscanf(corpus_file,
			"doc_id:%d sent_num:%d word_num:%d",
			&doc_id,
			&sent_num,
			&length) == 3) {
		if (read_doc_num >= doc_num) {
			fprintf(stderr,
					"%s:%d ERROR: read doc num is %d\n",
					__FILE__,
					__LINE__,
					read_doc_num);
			break;
		}
		Document * cur_doc = docs + read_doc_num;
		cur_doc->Init(doc_id, sent_num, length);
		int read_sent_num = 0;	// 已经读取的句子数目
		int read_word_num = 0;  // 计算offset
		int sent_length;
		int sent_id;

		// 逐行读取句子
		for (; read_sent_num < sent_num; read_sent_num++) {
			if (fscanf(corpus_file,
					"sent_id:%d length:%d",
					&sent_id,
					&sent_length) != 2) {
				fprintf(stderr,
						"%s:%d ERROR: Read corpus file failed!\n",
						__FILE__,
						__LINE__);
				fclose(corpus_file);
				return -1;
			}

			Sentence * cur_sent = cur_doc->sentences + read_sent_num;
			cur_sent->Init(sent_id, sent_length, read_word_num);

			// 读取句子中的词
			for (int word_ind = 0; word_ind < sent_length; ++ word_ind) {
				int word_id = -1;
				if (fscanf(corpus_file, "%d", &word_id) != 1) {
					fprintf(stderr,
							"%s:%d ERROR: Read corpus file failed!\n",
							__FILE__,
							__LINE__);
					fclose(corpus_file);
					return -1;
				}
				cur_sent->words[word_ind] = word_id;
			}
			read_word_num += sent_length;
		}
		read_doc_num++;
	}
	return read_doc_num;
}
