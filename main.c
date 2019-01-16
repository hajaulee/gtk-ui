#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include "string-constant.h"

GtkWidget * sfDialog;
GtkWidget * siDialog;
GtkWidget * inputNameChannelDialog;
GtkWidget * chatWindow;
GtkWidget * resultDialog;
GtkWidget * inputUsername;
GtkWidget * inputChannel;
void    initSelectFunctionDialog();
void    showSelectFuntionDialog();


int main(int argc, char *argv[])
{

	//to be thread-aware
    if (!g_thread_supported ()){ g_thread_init(NULL); }
	// initialize GDK thread support
	gdk_threads_init();

	// acquire the GDK lock
	gdk_threads_enter();

    // Run a function in main thread, safe for updating UI
	//g_timeout_add(100, (GSourceFunc)timer_exe, NULL);
	gtk_init(&argc, &argv);
	// gdk_threads_enter();
	
    initAll();
	showSelectFuntionDialog();


	gtk_main();

	// release the GDK lock
	gdk_threads_leave();
	return 0;
}

void onExit(){
    exit(0);
}
void initAll(){
    initSelectFunctionDialog();
    initSelectInfoDialog();
    initInputNameAndChannelDialog();
}
void showSelectInfoDialog(){
    gtk_widget_hide(sfDialog);
    showDialog(siDialog);
}
void initSelectInfoDialog(){
    siDialog = gtk_dialog_new_with_buttons(INFO_BUTTON, NULL,
											  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
    GtkWidget *dialog_ground = gtk_fixed_new();
	GtkWidget *inputGroupBox;
	GtkWidget *inputBox;
	GtkWidget *xsmbButton;
    GtkWidget *weatherButton;
    GtkWidget *sisButton;
    GtkWidget *backButton = gtk_button_new_with_label(BACK_BUTTON);
	//Khoi tao inputGroupBox
	inputGroupBox = gtk_frame_new(SELECT_FUNCTION);
    gtk_widget_set_size_request(inputGroupBox, 500, 200);
	//Khoi tao inputBox chua nut
	inputBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(inputGroupBox), inputBox);


	// button
	weatherButton = gtk_button_new_with_label(WEATHER_BUTTON);
	gtk_widget_set_margin_bottom(weatherButton, 0);
	gtk_widget_set_margin_top(weatherButton, 0);

    xsmbButton = gtk_button_new_with_label(XSMB_BUTTON);
	gtk_widget_set_margin_bottom(xsmbButton, 0);
	gtk_widget_set_margin_top(xsmbButton, 0);

    sisButton = gtk_button_new_with_label(SIS_BUTTON);
	gtk_widget_set_margin_bottom(sisButton, 0);
	gtk_widget_set_margin_top(sisButton, 0);

    gtk_fixed_put(GTK_FIXED(dialog_ground), inputGroupBox, 30, 30);
    gtk_fixed_put(GTK_FIXED(dialog_ground), backButton, 30, 0);
	gtk_box_pack_start(GTK_BOX(inputBox), weatherButton, TRUE, TRUE, 20);
	gtk_box_pack_start(GTK_BOX(inputBox), xsmbButton, TRUE, TRUE, 20);
    gtk_box_pack_start(GTK_BOX(inputBox), sisButton, TRUE, TRUE, 20);
	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(siDialog))), dialog_ground, TRUE, TRUE, 0);
    g_signal_connect(backButton, "clicked", G_CALLBACK(showSelectFuntionDialog), NULL);
}
void showDialog(GtkWidget * dialog){
    gtk_widget_show_all(dialog);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
void showSelectFuntionDialog(){
    gtk_widget_hide(siDialog);
    gtk_widget_hide(inputNameChannelDialog);
    showDialog(sfDialog);
}
void showInputNameAndChannelDialog(){
    gtk_widget_hide(sfDialog);
    showDialog(inputNameChannelDialog);
}
void initInputNameAndChannelDialog()
{
	inputNameChannelDialog = gtk_dialog_new_with_buttons(NAME_CHANNEL, NULL,
											  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);

	GtkWidget *dialog_ground = gtk_fixed_new();
	GtkWidget *tframe = gtk_frame_new(USERNAME);
	GtkWidget *bframe = gtk_frame_new(CHANNELNAME);
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *loginButton = gtk_button_new_with_label(LOGIN);
	GtkWidget *cancelButton = gtk_button_new_with_label(CANCEL);

    GtkWidget *backButton = gtk_button_new_with_label(BACK_BUTTON);
	inputUsername = gtk_entry_new();
	inputChannel = gtk_entry_new();

	gtk_box_pack_start(GTK_BOX(box), loginButton, TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(box), cancelButton, TRUE, TRUE, 2);

	gtk_widget_set_size_request(tframe, 300, 50);
	gtk_widget_set_size_request(bframe, 300, 50);
	gtk_widget_set_size_request(box, 300, 50);
	gtk_widget_set_size_request(loginButton, 100, 30);
	gtk_widget_set_size_request(cancelButton, 100, 30);

	gtk_widget_set_margin_start(inputUsername, 2);
	gtk_widget_set_margin_end(inputUsername, 2);
	gtk_widget_set_margin_start(inputChannel, 2);
	gtk_widget_set_margin_end(inputChannel, 2);

    gtk_fixed_put(GTK_FIXED(dialog_ground), backButton, 00, 0);
	gtk_fixed_put(GTK_FIXED(dialog_ground), tframe, 0, 50);
	gtk_fixed_put(GTK_FIXED(dialog_ground), bframe, 0, 110);
	gtk_fixed_put(GTK_FIXED(dialog_ground), box, 0, 250);

	gtk_container_add(GTK_CONTAINER(tframe), inputUsername);
	gtk_container_add(GTK_CONTAINER(bframe), inputChannel);

	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(inputNameChannelDialog))), dialog_ground, TRUE, TRUE, 0);
    g_signal_connect(backButton, "clicked", G_CALLBACK(showSelectFuntionDialog), NULL);
	// g_signal_connect(loginButton, "clicked", G_CALLBACK(onLoginButtonClicked), data_array);
	g_signal_connect(cancelButton, "clicked", G_CALLBACK(showSelectFuntionDialog), NULL);
	// g_signal_connect(inputUsername, "activate", G_CALLBACK(onLoginButtonClicked), data_array);
	// g_signal_connect(inputChannel, "activate", G_CALLBACK(onLoginButtonClicked), data_array);
	g_signal_connect(inputNameChannelDialog, "destroy", G_CALLBACK(onExit), NULL); //Ket thuc chuong trinh khi dong cua so chinh
	
}
void initSelectFunctionDialog()
{
	sfDialog = gtk_dialog_new_with_buttons(APP_TITLE, NULL,
											  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
    GtkWidget *dialog_ground = gtk_fixed_new();
	GtkWidget *inputGroupBox;
	GtkWidget *inputBox;
	GtkWidget *chatButton;
    GtkWidget *infoButton;
	//Khoi tao inputGroupBox
	inputGroupBox = gtk_frame_new(SELECT_FUNCTION);
    gtk_widget_set_size_request(inputGroupBox, 500, 200);
	//Khoi tao inputBox chua nut
	inputBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add(GTK_CONTAINER(inputGroupBox), inputBox);


	// button
	infoButton = gtk_button_new_with_label(INFO_BUTTON);
	gtk_widget_set_margin_bottom(infoButton, 20);
	gtk_widget_set_margin_top(infoButton, 20);

    chatButton = gtk_button_new_with_label(CHAT_BUTTON);
	gtk_widget_set_margin_bottom(chatButton, 20);
	gtk_widget_set_margin_top(chatButton, 20);

    gtk_fixed_put(GTK_FIXED(dialog_ground), inputGroupBox, 20, 20);
	gtk_box_pack_start(GTK_BOX(inputBox), infoButton, TRUE, TRUE, 20);
	gtk_box_pack_start(GTK_BOX(inputBox), chatButton, TRUE, TRUE, 20);

	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(sfDialog))), dialog_ground, TRUE, TRUE, 0);

	g_signal_connect(infoButton, "clicked", G_CALLBACK(showSelectInfoDialog), NULL);
    g_signal_connect(chatButton, "clicked", G_CALLBACK(showInputNameAndChannelDialog), NULL);
	g_signal_connect(sfDialog, "destroy", G_CALLBACK(onExit), NULL); //Ket thuc chuong trinh khi dong cua so chinh
}

