/*
 * corpus.h
 *
 *  Created on: 2014年1月17日
 *      Author: zhangrui04
 */

#ifndef CORPUS_H_
#define CORPUS_H_

#include <string>

class Sentence {
public:
	int sent_id;	//句子的id
	int length;  // n_d_s
	int * words;
	int offset; // 句子在doc中的offset，以token为单位
	int * words_which_window;	// words属于哪个window; v_d_s_n
	int * words_local_topic; // words是哪个local_topic; 如果-1表示其是global_topic, r_d_s_n
	int * words_global_topic; // words是那个gl_topic；如果-1表示其是local_topic, z_d_s_n
	int * wc_which_window; // 在某个句子中，words属于某个window的有几个; n_d_s_v

public:
	Sentence() {
		sent_id = 0;
		length = 0;
		offset = 0;
		words = NULL;
		wc_which_window = NULL;
		words_global_topic = NULL;
		words_local_topic = NULL;
		words_which_window = NULL;
	}
	Sentence(int s_id, int l, int off = 0) {
		sent_id = s_id;
		length = l;
		offset = off;
		if (length > 0) {
			words = new int[length];
		} else {
			words = NULL;
		}
		words_global_topic = NULL;
		words_local_topic = NULL;
		words_which_window = NULL;
		wc_which_window = NULL;
	}
	~Sentence() {
		if (words) {
			delete [] words;
		}
		if (words_global_topic) {
			delete[] words_global_topic;
		}
		if (words_local_topic) {
			delete [] words_local_topic;
		}
		if (words_which_window) {
			delete [] words_which_window;
		}
		if (wc_which_window) {
			delete [] wc_which_window;
		}
	}
	void Init(int s_id, int l, int off) {
		sent_id = s_id;
		length = l;
		offset = off;
		if (length > 0) {
			words = new int[length];
		} else {
			words = NULL;
		}
	}
};

class Document {
public:
	int doc_id;
	int sentence_num;
	int word_num;
	int sliding_window_num;

public:
	Sentence * sentences;
	// 分配到某个滑动窗口中的word_count, n_d_v
	int * wc_in_s_window;
	// 分配到某个滑动窗口中，topic类型为gl的word_count, n_d_v_gl
	int * gl_wc_in_s_window;
	// 分配到某个滑动窗口中，topic类型为loc的word_count, n_d_v_loc
	int * loc_wc_in_s_window;
	// 分配到某个滑动窗口中，gl_topic_id的word_count
	int * wc_in_s_window_with_gl_topic;
	// 分配到某个滑动窗口中，loc_topic_id的word_count, n_d_v_loc_z
	int * wc_in_s_window_with_loc_topic;
	// 分配到某个global_topic中的word_count, n_d_gl_z
	int * wc_with_gl_topic;
	// 分配到某个local_topic中的word_count
	int * wc_with_loc_topic;

	int wc_global; // n_d_gl
	int wc_local;

public:
	Document() {
		doc_id = 0;
		sentence_num = 0;
		word_num = 0;
		sliding_window_num = 0;
		wc_global = 0;
		wc_local = 0;
		sentences = NULL;
		wc_in_s_window = NULL;
		gl_wc_in_s_window = NULL;
		loc_wc_in_s_window = NULL;
		wc_in_s_window_with_gl_topic = NULL;
		wc_in_s_window_with_loc_topic = NULL;
		wc_with_gl_topic = NULL;
		wc_with_loc_topic = NULL;
	}

	Document(int d_id, int sent_num, int l) {
		doc_id = d_id;
		sentence_num = sent_num;
		word_num = l;
		sliding_window_num = 0;
		if (sentence_num > 0) {
			sentences = new Sentence[sentence_num];
		} else {
			sentences = NULL;
		}
		wc_global = 0;
		wc_local = 0;
		wc_in_s_window = NULL;
		gl_wc_in_s_window = NULL;
		loc_wc_in_s_window = NULL;
		wc_in_s_window_with_gl_topic = NULL;
		wc_in_s_window_with_loc_topic = NULL;
		wc_with_gl_topic = NULL;
		wc_with_loc_topic = NULL;
	}

	~Document() {
		if (sentences) {
			delete [] sentences;
		}
		if (wc_in_s_window) {
			delete [] wc_in_s_window;
		}
		if (gl_wc_in_s_window) {
			delete [] gl_wc_in_s_window;
		}
		if (loc_wc_in_s_window) {
			delete [] loc_wc_in_s_window;
		}
		if (wc_in_s_window_with_gl_topic) {
			delete [] wc_in_s_window_with_gl_topic;
		}
		if (wc_in_s_window_with_loc_topic) {
			delete [] wc_in_s_window_with_loc_topic;
		}
		if (wc_with_gl_topic) {
			delete [] wc_with_gl_topic;
		}
		if (wc_with_loc_topic) {
			delete [] wc_with_loc_topic;
		}
	}

	void Init(int d_id, int sent_num, int l) {
		doc_id = d_id;
		sentence_num = sent_num;
		word_num = l;
		if (sentence_num > 0) {
			sentences = new Sentence[sentence_num];
		} else {
			sentences = NULL;
		}
	}
};

class Corpus {
public:
	int doc_num;
	Document * docs;
public:
	Corpus(int d_num) {
		doc_num = d_num;
		if (doc_num > 0) {
			docs = new Document[d_num];
		} else {
			docs = NULL;
		}
	}
	~Corpus() {
		if (docs) {
			delete [] docs;
		}
	}
	int Load(const std::string corpus_file_path);
};

#endif /* CORPUS_H_ */
