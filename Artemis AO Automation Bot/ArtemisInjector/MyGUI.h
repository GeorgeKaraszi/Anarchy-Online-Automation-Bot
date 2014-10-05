#pragma once

namespace ArtemisInjector {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyGUI
	/// </summary>
	public ref class MyGUI : public System::Windows::Forms::Form
	{
	public:
		MyGUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyGUI()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::Label^  label1;
    protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(128, 68);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(116, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Looking For Applcation";
            // 
            // MyGUI
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(374, 138);
            this->Controls->Add(this->label1);
            this->Name = L"MyGUI";
            this->Text = L"Artemis Injector";
            this->Load += gcnew System::EventHandler(this, &MyGUI::MyGUI_Load);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private: System::Void MyGUI_Load(System::Object^  sender, System::EventArgs^  e) {
    }
    };
}
