#include "structures.h"

using namespace std;

void Qsort( struct Score arr[], int l, int r) {
	int i;

	if( l < r ) {
		i = partition( arr, l, r);
		Qsort( arr, l, i-1);
		Qsort( arr, i+1, r);
   }

}



int partition( struct Score a[], int l, int r) {

	int i, j;

		int id;
		double t,pivot;
		pivot = a[l].s;
		i = l; j = r+1;
		while(1) {

   			do ++i; while( a[i].s >= pivot && i <= r );

   			do --j; while( a[j].s < pivot );

   			if( i >= j ) break;

   			t = a[i].s; a[i].s = a[j].s; a[j].s = t;
   			id = a[i].id; a[i].id = a[j].id; a[j].id = id;
		}

	   t = a[l].s;
	   a[l].s = a[j].s;
	   a[j].s = t;

	   id = a[l].id;
	   a[l].id = a[j].id;
	   a[j].id = id;

	   return j;

}
