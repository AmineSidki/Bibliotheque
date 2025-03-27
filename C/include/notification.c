#include "notification.h"
#include "stdlib.h"
#include "stdio.h"
#include "utils.h"
#include "string.h"
#include "date.h"


// cette variable contient le dernier identifiant notification généré
int last_notification_id = 0;


Notification *string_to_notification(char *str)
{
    // splitting the string
    int length;
    char **split_string = split(str, delimiter, &length);

    // checking if all the fields are present
    if (length != 5)
    {
        printf("Erreur de lecture du fichier notification");
        return NULL;
    }

    // parsing the string
    Notification *notification      = (Notification*) malloc(sizeof(Notification));
    notification->id                = atoi(split_string[0]);
    notification->id_client         = atoi(split_string[1]);
    notification->notification_type = atoi(split_string[2]);
    notification->notification_text = split_string[3];
    notification->date_notification = string_to_date(split_string[4]);

    return notification;
}


char *notification_to_string(Notification *notification)
{
    char id[10];
    char client_id[10];
    char type[10];
    itoa(notification->id, id, 10);
	itoa(notification->id_client, client_id, 10);
	itoa(notification->notification_type, type, 10);

    // the buffer
    char *buffer = (char *) calloc(2048, sizeof(char));
    strcat(buffer, id);
    strcat(buffer, "#");
    strcat(buffer, client_id);
    strcat(buffer, "#");
    strcat(buffer, type);
    strcat(buffer, "#");
    strcat(buffer, notification->notification_text);
    strcat(buffer, "#");
    strcat(buffer, date_to_string(notification->date_notification));

    return buffer;
}