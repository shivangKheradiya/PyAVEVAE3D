using System;
using System.Windows;
using Aveva.ApplicationFramework.Presentation;

namespace PyAVEVAE3DPlugin
{
    public class InvokePythonConsoleCmd : Command
    {
        public InvokePythonConsoleCmd()
        {
            base.Key = "PyAVEVAE3DAddin.InvokePythonConsoleCmd";
        }

        public override void Execute()
        {
            try
            {
                MessageBox.Show("Hii It's Working");
            }
            catch (System.Exception ex)
            {
                Console.Write(ex.Message);
            }
        }
    }
}