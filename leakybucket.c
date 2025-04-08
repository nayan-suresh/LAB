#include<stdio.h>

void main() {
    int bucket_size, outgoing, current, incoming, n;
    current = 0;
    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);
    printf("Enter no of packets: ");
    scanf("%d", &n);
    printf("Enter outgoing rate: ");
    scanf("%d", &outgoing);

    printf("Initial bucket status: %d out of %d\n", current, bucket_size);

    while (n > 0) {
        printf("Enter incoming packet size: ");
        scanf("%d", &incoming);

        printf("Incoming packet size: %d\n", incoming);

        if (incoming <= bucket_size - current) {
            current += incoming;
            printf("Bucket status: %d out of %d\n", current, bucket_size);
        } else {
            printf("Dropped packets: %d\n", incoming - (bucket_size - current));
            current = bucket_size;
            printf("Bucket status: %d out of %d\n", current, bucket_size);
        }

        current -= outgoing;
        if (current < 0) current = 0;

        printf("After sending, bucket status: %d out of %d\n", current, bucket_size);
        n--;
    }
}
