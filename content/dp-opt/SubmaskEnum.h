/**
 * Author: Jayeon Yi
 * License: CC0
 * Source:
 * Description: Iterating through all masks with their submasks. Complexity $O(3^n)$
 */

for (int m=0; m<(1<<n); ++m)
    for (int s=m; s; s=(s-1)&m)
        (... s and m ...)