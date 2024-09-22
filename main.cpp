#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Scroll.H>
#include <vector>
#include <string>

// Global pointers to UI elements
Fl_Box* task_box;
std::vector<std::string> tasks;

// Function to update the task list display
void update_tasks() {
    std::string task_list;
    for (const auto& task : tasks) {
        task_list += "- " + task + "\n";
    }
    task_box->label(task_list.c_str());
    task_box->redraw();
}

// Callback function for the "Add Task" button
void add_task(Fl_Widget* widget, void* input_ptr) {
    Fl_Input* task_input = (Fl_Input*)input_ptr;
    const char* task = task_input->value();
    if (strlen(task) > 0) {
        tasks.push_back(task);
        task_input->value("");
    }
    update_tasks();
}

int main(int argc, char** argv) {
    Fl_Window* window = new Fl_Window(400, 400, "To-Do List");

    // Task input
    Fl_Input* task_input = new Fl_Input(100, 20, 200, 30, "New Task:");
    task_input->align(FL_ALIGN_LEFT);

    // Add Task button
    Fl_Button* add_button = new Fl_Button(150, 60, 100, 30, "Add Task");
    add_button->callback(add_task, (void*)task_input);

    // Task list display
    task_box = new Fl_Box(20, 100, 360, 260, "");
    task_box->box(FL_DOWN_FRAME);
    task_box->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP_LEFT);
    task_box->labelsize(14);
    task_box->labelfont(FL_COURIER);

    window->end();
    window->show(argc, argv);

    return Fl::run();
}
