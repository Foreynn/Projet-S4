#ifndef CHEMIN_H
#define CHEMIN_H

int SIZE; // The number of section.
struct trncn **trncns;
struct trncn **chemin_trouve;
int found_size;
struct point {int x; int y;};
struct point srt;
void get_chemin(struct point entry);

#endif
