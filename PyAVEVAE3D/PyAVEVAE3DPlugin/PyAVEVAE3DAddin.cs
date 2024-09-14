using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Aveva.ApplicationFramework;
using Aveva.ApplicationFramework.Presentation;

namespace PyAVEVAE3DPlugin
{
    public class PyAVEVAE3DAddin : IAddin
    {
        public string Name => "PyAVEVAE3DAddin";

        public string Description => "PyAVEVAE3DAddin Integrates Python into AVEVA E3D";

        public void Start(ServiceManager serviceManager)
        {
            CommandManager commandManager = (CommandManager)DependencyResolver.GetImplementationOf<ICommandManager>();
            commandManager.Commands.Add(new InvokePythonConsoleCmd());
        }

        public void Stop()
        {
            Console.Write("PyAVEVAE3DAddin is stoped.");
        }
    }
}
