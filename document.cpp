#include "document.h"


Document::Document(string title, string publication,
                   string datePublished, string text) {
    title_ = title;
    publication_ = publication;
    datePublished_ = datePublished;
    text_ = text;
}

void Document::setTitle(string title) {
    title_ = title;
}

string Document::getTitle() {
    return title_;
}

void Document::setPublication(string publication) {
    publication_ = publication;
}

string Document::getPublication() {
    return publication_;
}

void Document::setDate(string datePublish) {
    datePublished_ = datePublish;
}

string Document::setDate() {
    return datePublished_;
}

void Document::setText(string text){
    text_ = text;
}

string Document::getText(){
    return text_;
}

