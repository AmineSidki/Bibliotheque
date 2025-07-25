#include "notification.h"
#include "stdlib.h"
#include "stdio.h"
#include "utils.h"
#include "string.h"
#include "date.h"
#include "reader.h"



Notification *string_to_notification(char *str)
{
    // splitting the string
    int length;
    char **split_string = split(str, delimiter, &length);

    // checking if all the fields are present
    if (length != 5)
    {
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
    char id[10] = {0};
    char client_id[10] = {0};
    char type[10] = {0};
    my_itoa(notification->id, id, 10);
	my_itoa(notification->id_client, client_id, 10);
	my_itoa(notification->notification_type, type, 10);

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


Notification **load_notifications(int *length)
{
    // the list of clients
    Notification **notifications = (Notification **) calloc(1, sizeof(Notification *));
    *length = 0;

    char *file = read_file(fichier_notifications);
    if (file == NULL)
    {
        return NULL;
    }

    int len;
    char **notification_strings = split(file, '\n', &len);

    for (int i = 0; i < len; i++)
    {
        Notification *notification = string_to_notification(notification_strings[i]);
        if (notification == NULL)
        {
            return NULL;
        }

        notifications[(*length)++] = notification;
        notifications = (Notification**) realloc(notifications, (*length + 1) * sizeof(Notification*));
    }

    return notifications;
}

void save_notifications(Notification **notifications, int number)
{
    FILE *fptr = fopen(fichier_notifications, "w");
    if (fptr == NULL)
    {
        printf("Erreur de lecture du fichier notifications\n");
        return;
    }

    for (int i = 0; i < number - 1; i++)
    {
        fprintf(fptr, "%s\n", notification_to_string(notifications[i]));
    }

    fprintf(fptr, "%s", notification_to_string(notifications[number - 1]));
    fclose(fptr);
}