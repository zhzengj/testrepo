#include <cstdio>
int main()
{
	const char *res[] = {
"14 25 21 8 19 27 23 10 6 17 4 12 16 29 18 5 9 20 7 3 11 24 28 15 2 13 26 22 30",
"13 26 22 30 17 6 10 14 1 9 20 7 3 11 24 28 15 19 27 23 12 4 8 16 5 18 29 21 25",
"7 20 28 15 19 27 23 12 4 8 21 25 14 1 9 5 18 29 16 24 11 22 26 13 2 10 6 17 30",
"8 19 27 14 1 9 20 7 3 11 24 28 15 2 13 26 22 30 17 6 10 23 12 16 5 18 29 21 25",
"9 1 14 25 21 8 19 27 23 12 4 15 2 13 26 22 30 17 28 20 7 3 11 24 16 29 18 10 6",
"10 2 13 26 22 30 17 4 8 19 27 14 1 9 20 7 3 11 24 28 15 23 12 16 5 18 29 21 25",
"20 28 15 2 13 26 22 30 17 6 10 23 27 19 8 4 12 16 24 11 3 14 1 9 5 18 29 21 25",
"19 27 23 10 6 17 4 12 16 5 18 29 21 25 14 1 9 20 7 3 11 24 28 15 2 13 26 22 30",
"1 14 25 21 8 19 27 23 12 4 15 26 13 2 10 6 17 30 22 11 3 7 20 28 24 16 29 18 5",
"2 13 26 15 19 27 23 12 4 8 21 25 14 1 9 5 18 29 16 3 7 20 28 24 11 22 30 17 6",
"3 7 20 28 24 16 8 19 27 23 12 4 15 2 13 26 22 30 17 6 10 14 1 9 5 18 29 21 25",
"4 8 19 27 23 10 2 13 26 15 7 20 28 24 11 3 16 29 21 25 14 1 9 5 18 22 30 17 6",
"26 22 30 17 4 8 19 27 23 12 16 5 18 29 21 25 14 1 9 20 7 3 11 24 28 15 2 10 6",
"1 9 20 7 3 11 24 28 15 2 13 26 22 30 17 6 10 23 27 19 8 4 12 16 5 18 29 21 25",
"2 13 26 22 30 17 28 24 11 3 7 20 9 1 14 25 21 29 18 5 16 27 19 8 4 12 23 10 6",
"3 7 20 28 24 11 15 2 13 26 22 30 17 6 10 23 12 4 8 19 27 14 1 9 5 18 29 21 25",
"6 10 23 12 4 8 19 27 16 5 18 29 21 25 14 1 9 20 28 24 11 3 7 15 2 13 26 22 30",
"5 9 1 14 25 21 8 19 27 23 12 4 15 26 13 2 10 6 17 30 22 11 3 7 20 28 24 16 29",
"27 14 1 9 20 7 3 11 24 28 15 2 13 26 22 30 17 6 10 23 12 4 8 16 5 18 29 21 25",
"7 15 19 27 23 12 4 8 21 25 14 1 9 5 18 29 16 3 11 24 28 17 30 22 26 13 2 10 6",
"8 19 27 23 12 4 15 26 13 2 10 6 17 30 22 11 3 7 20 28 24 16 29 18 5 9 1 14 25",
"26 13 2 15 7 3 11 24 28 20 9 1 14 25 21 29 18 5 16 27 19 8 4 12 23 10 6 17 30",
"10 6 17 30 22 26 13 2 15 7 20 28 24 11 3 16 12 4 8 19 27 14 1 9 5 18 29 21 25",
"11 3 7 20 28 15 2 13 26 22 9 1 14 25 21 29 18 5 16 27 19 8 4 12 23 10 6 17 30",
"21 8 19 27 14 1 9 5 18 29 16 3 7 20 28 24 11 15 2 13 26 22 30 17 4 12 23 10 6",
"13 21 8 19 27 23 12 4 15 2 10 6 17 30 22 11 3 7 20 28 24 16 29 18 5 9 1 14 25",
"19 15 2 13 26 22 30 17 28 20 7 3 11 24 16 29 18 5 9 1 14 25 21 8 4 12 23 10 6",
"15 2 13 26 22 30 17 6 10 23 27 19 8 4 12 16 24 11 3 7 20 9 1 14 25 21 29 18 5",
"16 3 7 20 28 24 11 15 2 13 26 22 30 17 4 12 23 27 19 8 21 25 14 1 9 5 18 10 6",
"22 11 15 26 13 2 10 6 17 4 8 19 27 23 12 16 24 28 20 7 3 14 25 21 29 18 5 9 1"
};
int n;
do {
	scanf("%d", &n);
	if (-1 == n) break;
	printf("%d %s\n", n, res[n - 1]);
}while(1);
return 0;
}
