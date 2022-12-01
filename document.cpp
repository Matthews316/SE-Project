#include "document.h"


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
