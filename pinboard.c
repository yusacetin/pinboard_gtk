#include <gtk/gtk.h>

const int NAV_WRAP = 0; // whether navigation wrapping is allowed when using vim keys (1 for allow, anything else for disallow)

GtkWidget* table;
GtkWidget* window;
GtkWidget* buttons[16];

const int ROW_MINS[] = {0, 4, 8, 12};
const int ROW_MAXS[] = {3, 7, 11, 15};
gchar* values[16] = {
    "ಠ◡ಠ", "(・_・;)", "ヽ(°〇°)ﾉ", "( ͠° ͟ʖ ͡°)",
    "︶_︶", "¯\\_(ツ)_/¯", "( ͡° ʖ̯ ͡°)", "( ͡° ͜ʖ ͡°)",
    "(•﹏•)", "ಡ ͜ ʖ ಡ", "(;´༎ຶٹ༎ຶ`)", "(̴̦̦͎̤̰͓̔̒̀̎̇͛̒͒͘;̸̀̔́͛͒̽ ̛̬͔̤̽͒͗͊͠´̷̽͌̓̃̀̅̂͝͠ ̜̪̖̻̹̲͈̼́͜ͅ༎̵́  ̖ຶ̸̡̨̥̬͎̞͕͈͉̞͚̱̪͌̓͌ٹ̷̭͓̰͌̐༎̴͖͔͛͒̚ ̨̪̺̬ຶ̸ ̛̑̌̽̐̀͊̕͘̕͠ ̧̨̨͍͎̣̻̪̜͙̙̺̍`̷̧̛̩̀́͐̅̈́ ̡͈̺)̷͓̖̟̝̄͋̾̏͝",
    "(｡•́︿•̀｡)", "(ಥ﹏ಥ)", "(￢_￢)", "(ʘ ͟ʖ ʘ)"
};

gint get_focused_button_index(){
    GSList *children, *iter;
    gint index = 0;

    // Get the currently focused widget
    GtkWidget* focused_widget = gtk_window_get_focus(GTK_WINDOW(window));

    // Iterate over the table's children to find the focused widget
    children = gtk_container_get_children(GTK_CONTAINER(table));
    for (iter = children; iter != NULL; iter = g_slist_next(iter)){
        if (GTK_IS_WIDGET(iter->data) && GTK_WIDGET(iter->data) == focused_widget){
            index = 15 - index;
            //g_print("Focused widget index: %d\n", index);
            break;
        }
        index++;
    }
    g_slist_free(children);
    return index;
}


void free_data(gpointer data, GClosure* closure){
    free(data);
}

void copy_callback(GtkWidget *widget, gpointer data){
    char* text = gtk_button_get_label(GTK_BUTTON(widget));
    char command[1024];
    snprintf(command, sizeof(command), "echo -n '%s' | xclip -selection clipboard", text);
    system(command);

    g_print(text);
    g_print("\n");
    gtk_main_quit();
}

void focus(GtkWidget* button){
    gtk_widget_grab_focus(button);
}

gboolean key_press_callback(GtkWidget *widget, GdkEventKey *event, gpointer data){
    if (event->keyval == GDK_KEY_Escape){
        gtk_main_quit();
        return TRUE;
    }
    if (event->keyval == GDK_KEY_l || event->keyval == GDK_KEY_Right){
        gint current_index = get_focused_button_index();
        int new_index = current_index + 1;
        if (NAV_WRAP != 1){
            int current_row;
            if (current_index < 4){current_row = 0;}
            else if (current_index < 8){current_row = 1;}
            else if (current_index < 12){current_row = 2;}
            else{current_row = 3;}
            if (new_index < ROW_MINS[current_row]){new_index = current_index;}
            else if (new_index > ROW_MAXS[current_row]){new_index = current_index;}
        }
        if (new_index > 15){
            if (NAV_WRAP == 1){
                new_index = 0;
            }else{
                new_index = current_index;
            }
        }
        focus(buttons[new_index]);
        return TRUE;
    }
    else if (event->keyval == GDK_KEY_h || event->keyval == GDK_KEY_Left){
        gint current_index = get_focused_button_index();
        int new_index = current_index - 1;
        if (NAV_WRAP != 1){
            int current_row;
            if (current_index < 4){current_row = 0;}
            else if (current_index < 8){current_row = 1;}
            else if (current_index < 12){current_row = 2;}
            else{current_row = 3;}
            if (new_index < ROW_MINS[current_row]){new_index = current_index;}
            else if (new_index > ROW_MAXS[current_row]){new_index = current_index;}
        }
        if (new_index < 0){
            if (NAV_WRAP == 1){
                new_index = 15;
            }else{
                new_index = current_index;
            }
        }
        focus(buttons[new_index]);
        return TRUE;
    }
    else if (event->keyval == GDK_KEY_j || event->keyval == GDK_KEY_Down){
        gint current_index = get_focused_button_index();
        int new_index = current_index + 4;
        if (new_index > 15){
            if (NAV_WRAP == 1){
                new_index = new_index - 16;
            }else{
                new_index = current_index;
            }
        }
        focus(buttons[new_index]);
        return TRUE;
    }
    else if (event->keyval == GDK_KEY_k || event->keyval == GDK_KEY_Up){
        gint current_index = get_focused_button_index();
        int new_index = current_index - 4;
        if (new_index < 0){
            if (NAV_WRAP == 1){
                new_index = new_index + 16;
            }else{
                new_index = current_index;
            }
        }
        focus(buttons[new_index]);
        return TRUE;
    }
    return FALSE;
}

// GTK program template from https://zetcode.com/gui/gtk2/gtklayoutmanagement/
int main(int argc, char *argv[]){
    GtkWidget *button;
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
            if (i == 0 && j == 0)
            {
                gtk_widget_grab_focus(button);
            }
            buttons[i*4 + j] = button;
            pos++;
        }
    }

    gtk_container_add(GTK_CONTAINER(window), table);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(key_press_callback), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}