/**
 * Author: Jaechan Lee
 * License: CC0
 * Source:
 * Description: Find $F[mask] = \sum_{i \in mask} A[i]$ in $O(N * 2^N)$.
 */

for(int i = 0; i < (1 << N); i++) F[i] = A[i];
for(int j = 0; j < N; j++) for(int i = 0; i < (1 << N); i++)
	if(i & (1 << j)) F[i] += F[i ^ (1 << j)];
