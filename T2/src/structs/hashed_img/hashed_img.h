#pragma once


typedef struct hashed_img
{
	int position;
	struct hashed_img* next;  
} HashedImg;

HashedImg* init_hashed_img(int position);
void destroy_hashed_imgs(HashedImg* hashedImg);