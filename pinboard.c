#include <gtk/gtk.h>

void copy_callback(GtkWidget *widget, gpointer data)
{
    GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    char* text = gtk_button_get_label(widget);
    gtk_clipboard_set_text(clipboard, text, -1);
    g_print(text);
    g_print("\n");
    gtk_main_quit();
}

void keyboard_quit(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Escape) {
        gtk_main_quit();
    }
}

// GTK program template from https://zetcode.com/gui/gtk2/gtklayoutmanagement/
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *button;

    gchar *values[16] = {
        "ಠ◡ಠ", "(・_・;)", "ヽ(°〇°)ﾉ", "( ͠° ͟ʖ ͡°)",
        "︶_︶", "¯\\_(ツ)_/¯", "( ͡° ʖ̯ ͡°)", "( ͡° ͜ʖ ͡°)",
        "(•﹏•)", "ಡ ͜ ʖ ಡ", "(;´༎ຶٹ༎ຶ`)", "(̴̦̦͎̤̰͓̔̒̀̎̇͛̒͒͘;̸̀̔́͛͒̽ ̛̬͔̤̽͒͗͊͠´̷̽͌̓̃̀̅̂͝͠ ̜̪̖̻̹̲͈̼́͜ͅ༎̵́  ̖ຶ̸̡̨̥̬͎̞͕͈͉̞͚̱̪͌̓͌ٹ̷̭͓̰͌̐༎̴͖͔͛͒̚ ̨̪̺̬ຶ̸ ̛̑̌̽̐̀͊̕͘̕͠ ̧̨̨͍͎̣̻̪̜͙̙̺̍`̷̧̛̩̀́͐̅̈́ ̡͈̺)̷͓̖̟̝̄͋̾̏͝",
        "(｡•́︿•̀｡)", "(ಥ﹏ಥ)", "(￢_￢)", "(ʘ ͟ʖ ʘ)"
    };

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 180);
    gtk_window_set_title(GTK_WINDOW(window), "Pinboard");

    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    table = gtk_table_new(4, 4, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 2);
    gtk_table_set_col_spacings(GTK_TABLE(table), 2);

    int i = 0;
    int j = 0;
    int pos = 0;

    for (i=0; i < 4; i++) {
        for (j=0; j < 4; j++) {
            button = gtk_button_new_with_label(values[pos]);
            gtk_table_attach_defaults(GTK_TABLE(table), button, j, j+1, i, i+1);
            g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(copy_callback), NULL);
            pos++;
        }
    }

    gtk_container_add(GTK_CONTAINER(window), table);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(keyboard_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}