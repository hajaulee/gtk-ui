#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include "string-constant.h"

GtkWidget * sfDialog;
GtkWidget * siDialog;
GtkWidget * sisLoginDialog;
GtkWidget * inputNameDialog;
GtkWidget * inputChannelDialog;
GtkWidget * chatWindow;
GtkWidget * resultDialog;
GtkWidget * inputUsername;
GtkWidget * inputChannel;
GtkWidget * inputHocKy;
GtkWidget * inputPassword;
GtkWidget * inputMssv;
GtkWidget * chatArea;
GtkWidget * messageInput;
GtkWidget *  chatOutputScroller;
GtkWidget *frame;

char name[100]; // store user name
char channel [100]; // store channel name
char message[200]; // store user input
char channelMessage[4096]; // store all message for display
void    initSelectFunctionDialog();
void    showSelectFuntionDialog();
void set_pos(GtkWidget *gw, int x, int y)
{
	gtk_fixed_put(GTK_FIXED(frame), gw, x, y);
}
void set_size(GtkWidget *gw, int width, int height)
{
	gtk_widget_set_size_request(gw, width, height);
}
void textViewSetText(GtkWidget *textView, char *text)// thay doi text trong o hien thi tin nhan
{
	char *x, *q;
	GtkTextBuffer *t_buffer;
	GtkTextIter start;
	GtkTextIter end;
	t_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	if (t_buffer == NULL)
	{
		printf("Get buffer fail!");
		t_buffer = gtk_text_buffer_new(NULL);
	}
	gtk_text_buffer_set_text(t_buffer, text, -1);
	GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(chatOutputScroller));
	gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj));
	gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(chatOutputScroller), adj);
}
void onSendButtonClicked(){ // Su kien nhap tin nhan
	strcpy(message, gtk_entry_get_text(GTK_ENTRY(messageInput)));
	if(strcmp(message, "/out") == 0){
		showInputChannelDialog();
		return;
	}
	gtk_entry_set_text(GTK_ENTRY(messageInput), "");
	strcat(channelMessage, message);
	textViewSetText(GTK_TEXT_VIEW(chatArea), channelMessage);
	puts(message);
}
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
	// showMainWindow();

	gtk_main();

	// release the GDK lock
	gdk_threads_leave();
	return 0;
}

void onExit(){
    exit(0);
}
void showMessage(GtkWidget *parent, GtkMessageType type, char *mms, char *content)
{
	GtkWidget *mdialog;
	mdialog = gtk_message_dialog_new(GTK_WINDOW(parent),
									 GTK_DIALOG_DESTROY_WITH_PARENT,
									 type,
									 GTK_BUTTONS_OK,
									 "%s", mms);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s", content);
	gtk_widget_show_all(mdialog);
	gtk_dialog_run(GTK_DIALOG(mdialog));
	gtk_widget_destroy(mdialog);
}

void handleXSMB(){
    // code here
    char * result = "Ngày: 16/01/2019\nMã trúng giải: 4GU-12GU-7GU\nĐB: 22086\nG1: 79312\nG2: 90049 - 54062\nG3: 72537 - 10294 - 62485\n"
	"\t99403 - 26631 - 73265\nG4: 3694 - 2907 - 6472 - 2670\nG5: 1937 - 7578 - 4575\n\t5576 - 4557 - 3331\nG6: 257 - 886 - 750\nG7: 28 - 97 - 31 - 95\n";
    showMessage(siDialog, GTK_MESSAGE_INFO, "Thong tin xsmb", result);
}
void handleWeather(){
    showMessage(siDialog, GTK_MESSAGE_INFO, "Weather", "Thong tin thoi tiet");
}
void handleSis(){
	char mssv[20], password[100], hocky[10];
	strcpy(mssv, gtk_entry_get_text(GTK_ENTRY(inputMssv)));
	strcpy(password, gtk_entry_get_text(GTK_ENTRY(inputPassword)));
	strcpy(hocky, gtk_entry_get_text(GTK_ENTRY(inputHocKy)));

	printf("%s/%s/%s\n",mssv, password, hocky);
	// code here


	char * result = 
	"Tiếng Anh VN VI   [7.5 6 C+]\n"
	"Lý thuyết mạch logic   [4 6 D+]\n"
	"Thực hành mạch logic   [9 7 B]\n"
	"Thực hành cơ sở dữ liệu   [8.5 9.5 A]\n"
	"Cơ sở dữ liệu   [9.5 10 A+]\n"
	"Tiếng Nhật 5   [9 8.5 A]\n"
	"Tiếng Nhật chuyên ngành 1   [8.5 8.5 A]\n"
	"Bóng chuyền II   [5 6 C]\n"
	"GPA: 3.38\t\tCPA: 3.64\n";

    showMessage(siDialog, GTK_MESSAGE_INFO, "Sis", result);
}

/**********************************************


Khong quan tam phia duoi nay



************************************************/
void initAll(){
    initSelectFunctionDialog();
    initSelectInfoDialog();
    initInputNameDialog();
	initInputChannelDialog();
	initMainWindow();
	initSisLoginDialog();
}
void showSelectInfoDialog(){
    gtk_widget_hide(sfDialog);
	gtk_widget_hide(sisLoginDialog);
    showDialog(siDialog);
}
void initSisLoginDialog()
{
	sisLoginDialog = gtk_dialog_new_with_buttons(LOGIN, NULL,
											  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);

	GtkWidget *dialog_ground = gtk_fixed_new();
	GtkWidget *tframe = gtk_frame_new(MSSV);
	GtkWidget *bframe = gtk_frame_new(PASSWORD);
	GtkWidget *cframe = gtk_frame_new(HOC_KY);
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *loginButton = gtk_button_new_with_label(TRA_CUU);
	GtkWidget *cancelButton = gtk_button_new_with_label(CANCEL);
	inputMssv = gtk_entry_new();
	inputPassword = gtk_entry_new();
	inputHocKy = gtk_entry_new();

	gtk_entry_set_visibility(GTK_ENTRY(inputPassword), FALSE);

	gtk_box_pack_start(GTK_BOX(box), loginButton, TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(box), cancelButton, TRUE, TRUE, 2);

	set_size(tframe, 300, 50);
	set_size(bframe, 300, 50);
	set_size(cframe, 300, 50);
	set_size(box, 300, 50);
	set_size(loginButton, 100, 30);
	set_size(cancelButton, 100, 30);

	gtk_widget_set_margin_start(inputMssv, 2);
	gtk_widget_set_margin_end(inputMssv, 2);
	gtk_widget_set_margin_start(inputPassword, 2);
	gtk_widget_set_margin_end(inputPassword, 2);
	gtk_widget_set_margin_start(inputHocKy, 2);
	gtk_widget_set_margin_end(inputHocKy, 2);

	gtk_fixed_put(GTK_FIXED(dialog_ground), tframe, 0, 20);
	gtk_fixed_put(GTK_FIXED(dialog_ground), bframe, 0, 80);
	gtk_fixed_put(GTK_FIXED(dialog_ground), cframe, 0, 140);
	gtk_fixed_put(GTK_FIXED(dialog_ground), box, 0, 280);

	gtk_container_add(GTK_CONTAINER(tframe), inputMssv);
	gtk_container_add(GTK_CONTAINER(bframe), inputPassword);
	gtk_container_add(GTK_CONTAINER(cframe), inputHocKy);

	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(sisLoginDialog))), dialog_ground, TRUE, TRUE, 0);


	g_signal_connect(loginButton, "clicked", G_CALLBACK(handleSis), NULL);
	g_signal_connect(cancelButton, "clicked", G_CALLBACK(showSelectInfoDialog), NULL);
	g_signal_connect(inputMssv, "activate", G_CALLBACK(handleSis), NULL);
	g_signal_connect(inputPassword, "activate", G_CALLBACK(handleSis), NULL);
	g_signal_connect(sisLoginDialog, "destroy", G_CALLBACK(onExit), NULL); //Ket thuc chuong trinh khi dong cua so chinh

}

void showSisLoginDialog()
{
	gtk_widget_hide(siDialog);
	gtk_widget_show_all(sisLoginDialog);
	gtk_dialog_run(GTK_DIALOG(sisLoginDialog));
	return;
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
    g_signal_connect(xsmbButton, "clicked", G_CALLBACK(handleXSMB), NULL);
    g_signal_connect(sisButton, "clicked", G_CALLBACK(showSisLoginDialog), NULL);
    g_signal_connect(weatherButton, "clicked", G_CALLBACK(handleWeather), NULL);
}
void showDialog(GtkWidget * dialog){
    gtk_widget_show_all(dialog);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
void showSelectFuntionDialog(){
    gtk_widget_hide(siDialog);
    gtk_widget_hide(inputNameDialog);
    showDialog(sfDialog);
}
void showInputNameDialog(){
    gtk_widget_hide(sfDialog);
	gtk_widget_hide(inputChannelDialog);
    showDialog(inputNameDialog);
}

void showInputChannelDialog(){
    gtk_widget_hide(inputNameDialog);
	gtk_widget_hide(chatWindow);
    showDialog(inputChannelDialog);
}
GtkWidget *initChatArea(int x, int y)
{
	GtkWidget *outputBox;

	//khoi tao hop chua chatArea hien thi khung chat
	outputBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_size_request(outputBox, 450, 280);
	set_pos(outputBox, x, y);

	//Khung chat
	chatArea = gtk_text_view_new();
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(chatArea), GTK_WRAP_WORD_CHAR); //Chong tran be ngang

	//Khoi tao thanh keo truot cho chatArea
	chatOutputScroller = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(chatOutputScroller), chatArea);

	gtk_box_pack_start(GTK_BOX(outputBox), chatOutputScroller, TRUE, TRUE, 2);
	return chatArea;
}

GtkWidget *initMessageInput(int x, int y)
{
	GtkWidget *inputGroupBox;
	GtkWidget *inputBox;
	GtkWidget *sendButton;

	//Khoi tao inputGroupBox
	inputGroupBox = gtk_frame_new(TEXT_INPUT_LABEL);
	gtk_widget_set_size_request(inputGroupBox, 450, 60);
	set_pos(inputGroupBox, x, y);

	//Khoi tao inputBox chua o text va nut send
	inputBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add(GTK_CONTAINER(inputGroupBox), inputBox);

	//Khoi tao o nhap va chatArea hien thi nghia
	messageInput = gtk_entry_new();
	gtk_widget_set_size_request(messageInput, 388, 20);
	gtk_entry_set_placeholder_text(GTK_ENTRY(messageInput), "Enter \"out\" to back");
	//send button
	sendButton = gtk_button_new_with_label(SEND_LABEL);
	gtk_widget_set_margin_bottom(sendButton, 5);
	gtk_widget_set_margin_top(sendButton, 0);

	gtk_box_pack_start(GTK_BOX(inputBox), messageInput, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(inputBox), sendButton, TRUE, TRUE, 5);

	g_signal_connect(sendButton, "clicked", G_CALLBACK(onSendButtonClicked), NULL);
	g_signal_connect(messageInput, "activate", G_CALLBACK(onSendButtonClicked), NULL);
	return messageInput;
}
void initMainWindow()
{
	// Khoi tao cua so
	// chatWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// gtk_window_set_position(GTK_WINDOW(chatWindow), GTK_WIN_POS_CENTER);
	// //gtk_window_set_default_size(GTK_WINDOW(window), -1, -1);
	// gtk_window_set_title(GTK_WINDOW(chatWindow), APP_TITLE);
	// gtk_window_set_resizable(GTK_WINDOW(chatWindow), FALSE);
	chatWindow = gtk_dialog_new_with_buttons(CHAT_BUTTON, NULL,
											  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
	//Khoi tao nen
	frame = gtk_fixed_new();

	// gtk_container_add(GTK_CONTAINER(chatWindow), frame);
	gtk_widget_set_margin_bottom(frame, 5);
	gtk_widget_set_margin_end(frame, 5);

	initChatArea(5, 10);
	initMessageInput(5, 280);
	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(chatWindow))), frame, TRUE, TRUE, 0);
	g_signal_connect(chatWindow, "destroy", G_CALLBACK(onExit), NULL); //Ket thuc chuong trinh khi dong cua so chinh
}

void showMainWindow()
{
	gtk_widget_hide(inputChannelDialog);
	strcpy(name, gtk_entry_get_text(GTK_ENTRY(inputUsername)));
	strcpy(channel, gtk_entry_get_text(GTK_ENTRY(inputChannel)));
	// gtk_widget_show_all(chatWindow);
	showDialog(chatWindow);
	gtk_entry_grab_focus_without_selecting(GTK_ENTRY(messageInput));
	printf("hello\n");
}
void initInputChannelDialog(){
	inputChannelDialog = gtk_dialog_new_with_buttons(CHANNELNAME, NULL,
											  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);

	GtkWidget *dialog_ground = gtk_fixed_new();
	// GtkWidget *tframe = gtk_frame_new(USERNAME);
	GtkWidget *bframe = gtk_frame_new(CHANNELNAME);
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *loginButton = gtk_button_new_with_label(JOIN_CHANNEL);
	GtkWidget *cancelButton = gtk_button_new_with_label(CANCEL);

    GtkWidget *backButton = gtk_button_new_with_label(BACK_BUTTON);
	// inputUsername = gtk_entry_new();
	inputChannel = gtk_entry_new();

	gtk_box_pack_start(GTK_BOX(box), loginButton, TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(box), cancelButton, TRUE, TRUE, 2);

	// gtk_widget_set_size_request(tframe, 300, 50);
	gtk_widget_set_size_request(bframe, 300, 50);
	gtk_widget_set_size_request(box, 300, 50);
	gtk_widget_set_size_request(loginButton, 100, 30);
	gtk_widget_set_size_request(cancelButton, 100, 30);

	// gtk_widget_set_margin_start(inputUsername, 2);
	// gtk_widget_set_margin_end(inputUsername, 2);
	gtk_widget_set_margin_start(inputChannel, 2);
	gtk_widget_set_margin_end(inputChannel, 2);

    gtk_fixed_put(GTK_FIXED(dialog_ground), backButton, 00, 0);
	// gtk_fixed_put(GTK_FIXED(dialog_ground), tframe, 0, 50);
	gtk_fixed_put(GTK_FIXED(dialog_ground), bframe, 0, 50);
	gtk_fixed_put(GTK_FIXED(dialog_ground), box, 0, 110);
	gtk_container_add(GTK_CONTAINER(bframe), inputChannel);

	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(inputChannelDialog))), dialog_ground, TRUE, TRUE, 0);
    g_signal_connect(backButton, "clicked", G_CALLBACK(showInputNameDialog), NULL);
	g_signal_connect(loginButton, "clicked", G_CALLBACK(showMainWindow), NULL);
	g_signal_connect(cancelButton, "clicked", G_CALLBACK(showInputNameDialog), NULL);
	// g_signal_connect(inputUsername, "activate", G_CALLBACK(onLoginButtonClicked), data_array);
	// g_signal_connect(inputChannel, "activate", G_CALLBACK(onLoginButtonClicked), data_array);
	g_signal_connect(inputChannelDialog, "destroy", G_CALLBACK(onExit), NULL); //Ket thuc chuong trinh khi dong cua so chinh
	
}
void initInputNameDialog()
{
	inputNameDialog = gtk_dialog_new_with_buttons(NAME_CHANNEL, NULL,
											  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);

	GtkWidget *dialog_ground = gtk_fixed_new();
	GtkWidget *tframe = gtk_frame_new(USERNAME);
	// GtkWidget *bframe = gtk_frame_new(CHANNELNAME);
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *loginButton = gtk_button_new_with_label(LOGIN);
	GtkWidget *cancelButton = gtk_button_new_with_label(CANCEL);

    GtkWidget *backButton = gtk_button_new_with_label(BACK_BUTTON);
	inputUsername = gtk_entry_new();
	// inputChannel = gtk_entry_new();

	gtk_box_pack_start(GTK_BOX(box), loginButton, TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(box), cancelButton, TRUE, TRUE, 2);

	gtk_widget_set_size_request(tframe, 300, 50);
	// gtk_widget_set_size_request(bframe, 300, 50);
	gtk_widget_set_size_request(box, 300, 50);
	gtk_widget_set_size_request(loginButton, 100, 30);
	gtk_widget_set_size_request(cancelButton, 100, 30);

	gtk_widget_set_margin_start(inputUsername, 2);
	gtk_widget_set_margin_end(inputUsername, 2);
	// gtk_widget_set_margin_start(inputChannel, 2);
	// gtk_widget_set_margin_end(inputChannel, 2);

    gtk_fixed_put(GTK_FIXED(dialog_ground), backButton, 00, 0);
	gtk_fixed_put(GTK_FIXED(dialog_ground), tframe, 0, 50);
	// gtk_fixed_put(GTK_FIXED(dialog_ground), bframe, 0, 110);
	gtk_fixed_put(GTK_FIXED(dialog_ground), box, 0, 110);

	gtk_container_add(GTK_CONTAINER(tframe), inputUsername);
	// gtk_container_add(GTK_CONTAINER(bframe), inputChannel);

	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(inputNameDialog))), dialog_ground, TRUE, TRUE, 0);
    g_signal_connect(backButton, "clicked", G_CALLBACK(showSelectFuntionDialog), NULL);
	g_signal_connect(loginButton, "clicked", G_CALLBACK(showInputChannelDialog), NULL);
	g_signal_connect(cancelButton, "clicked", G_CALLBACK(showSelectFuntionDialog), NULL);
	// g_signal_connect(inputUsername, "activate", G_CALLBACK(onLoginButtonClicked), data_array);
	// g_signal_connect(inputChannel, "activate", G_CALLBACK(onLoginButtonClicked), data_array);
	g_signal_connect(inputNameDialog, "destroy", G_CALLBACK(onExit), NULL); //Ket thuc chuong trinh khi dong cua so chinh
	
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
    g_signal_connect(chatButton, "clicked", G_CALLBACK(showInputNameDialog), NULL);
	g_signal_connect(sfDialog, "destroy", G_CALLBACK(onExit), NULL); //Ket thuc chuong trinh khi dong cua so chinh
}


