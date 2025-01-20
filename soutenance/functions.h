#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <gtk/gtk.h>

void makeCharset(const char *options, char *charset);
int checkCharValid(const char *target, const char **algo); 
int bruteforce(char* argCharset, char* algo, char* maxStr, char* minStr, char* target);
void generateCombinations(const char *charset, char *current, int position, int length, char *algo, char* target);
int dictAtk(char *dict, char *algo, char *target);
int sha_hash(char *str, char *hash);
int md5_hash(char *str, char *hash);

// Fonction de l'interface GTK3
void show_logs();
void update_result_label(const char *message);
void log_password(const char *password, const char *hash); 
void on_show_logs_button_clicked(GtkWidget *widget, gpointer data);
void open_logs_file(GtkWidget *widget, gpointer data);
void show_error_message(GtkWidget *parent, const char *message);
void get_charset_options(char *options);
static void resolve_hash(GtkWidget *button, gpointer data);
static void open_file_dialog(GtkWidget *button, gpointer data);
static void activate(GtkApplication *app, gpointer user_data);

#endif // FUNCTIONS_H

