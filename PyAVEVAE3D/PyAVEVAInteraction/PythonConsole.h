#pragma once

#include <Python.h>
#include <vcclr.h>
#include "typecast.h"

namespace PythonEmbeddedApp {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class Form1 : public System::Windows::Forms::Form
    {
    public:
        Form1(void)
        {
            InitializeComponent();
            InitializePython();
        }

    protected:
        ~Form1()
        {
            if (components)
            {
                delete components;
            }
            FinalizePython();
        }

    private:
        System::Windows::Forms::TextBox^ inputTextBox;
        System::Windows::Forms::Button^ executeButton;
        System::Windows::Forms::TextBox^ outputTextBox;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
            this->executeButton = (gcnew System::Windows::Forms::Button());
            this->outputTextBox = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();

            // Input TextBox
            this->inputTextBox->Location = System::Drawing::Point(12, 12);
            this->inputTextBox->Multiline = true;
            this->inputTextBox->Size = System::Drawing::Size(360, 50);
            this->inputTextBox->TabIndex = 0;

            // Execute Button
            this->executeButton->Location = System::Drawing::Point(12, 68);
            this->executeButton->Size = System::Drawing::Size(75, 23);
            this->executeButton->Text = L"Execute";
            this->executeButton->Click += gcnew System::EventHandler(this, &Form1::executeButton_Click);

            // Output TextBox
            this->outputTextBox->Location = System::Drawing::Point(12, 97);
            this->outputTextBox->Multiline = true;
            this->outputTextBox->Size = System::Drawing::Size(360, 150);
            this->outputTextBox->TabIndex = 1;

            // Form1
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(384, 261);
            this->Controls->Add(this->outputTextBox);
            this->Controls->Add(this->executeButton);
            this->Controls->Add(this->inputTextBox);
            this->Name = L"Form1";
            this->Text = L"Python Embedded App";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void InitializePython()
        {
            //Py_Initialize();
        }

        void FinalizePython()
        {
            //Py_Finalize();
        }

        void executeButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            System::String^ input = inputTextBox->Text;
            PyObject* sys = PyImport_ImportModule("sys");
            PyObject* stringIO = PyImport_ImportModule("io");
            PyObject* pyOutput = PyObject_CallMethod(stringIO, "StringIO", nullptr);

            // Redirect Python stdout and stderr to StringIO
            PyObject_SetAttrString(sys, "stdout", pyOutput);
            PyObject_SetAttrString(sys, "stderr", pyOutput);

            if (PyRun_SimpleString(typecast::StringToCharP(input)) != 0) {
                // Handle any errors
                PyErr_Print();
            }
            PyObject* output = PyObject_CallMethod(pyOutput, "getvalue", nullptr);
            const char* outputStr = PyUnicode_AsUTF8(output);
            Py_XDECREF(output);
            Py_XDECREF(pyOutput);
            Py_XDECREF(sys);
            Py_XDECREF(stringIO);
            outputTextBox->Text = typecast::CharPToString(outputStr);
        }
    };
}