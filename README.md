# PyAVEVAE3D

PyAVEVAE3D contains Proof of Concept for Python 3 embedding into AVEVA Plant Design Products ( e.g. PDMS, E3D2.1/ 3.1, Diagrams, Engineering). These software are based on PML &amp; PML.Net.

This repository has Visual Studio Project Solution. The Solution contains 2 main projects:

- **PyAVEVAInteraction :** It contains the architectural skeleton for Python Embading into AVEVA E3D2.1.0.3. and It invoks the either system level python or virtual enviroment python.
- **PyAVEVAE3DExt :** It's Python extension module. It contains the c++ & python classes which allows python to directly interact with the AVEVA E3D.

## Build Environment Information

- AVEVA E3D Version : Mk2.1.0.3[Z2103-12]  (WINDOWS-NT 6.1)  (27 Apr 2016 : 23:54)
- Python : Python 3.10.4 (tags/v3.10.4:9d38120, Mar 23 2022, 22:57:10) [MSC v.1929 32 bit (Intel)] on win32
- Visual Studio : 2022

## Procedure For Utilizing the Enviroment

1.  Copy following files from solution to the pmllib folder,

    ```..\PyAVEVAE3D\PyAVEVAE3DExt\DataBridge.pmlobj```

    ```..\PyAVEVAE3D\PyAVEVAInteraction\RunPy.pmlfrm```
    
2. Create Python 32bit Virtual enviroment. and Create PML Global Variable for Accessing Python Virtual from E3D Session. Use the following pml command,
    
    ```
    !!pyVenv = |path to virtual environment/Scripts/python.exe|
    ```

3. Copy Dll files from solution to Aveva Installation Directory.

    From : ```..\PyAVEVAE3D\SampleDlls\PyAVEVAInteraction.dll```

    To : ```%AVEVA_DESIGN_EXE%```

4. copy pyd file or use pip install

5. Open RunPy form using pml command ```Show !!RunPy```. RunPy Form is used to write/ test python scripts.

6. Run Python Script form the Form. And All the output from python scripts will be printed in the AVEVA console. e.g. ```print("abc")``` in python will give the output in the python console.

## Procedure For Setting Up Development Enviroment

Refer the documetation Section for Detailed Procedure for setting up development environment.

## General Guideline

-- For Utilzing Python with Other AVEVA Software, Please install the Python version compatible to the AVEVA module architecture e.g. (x86, x64). and Make sure the platform architectural dependencies (Python and AVEVA Dll) for Build/ Release.

-- ```conda``` Environment as well conpatible. Make sure the ```conda``` environment platform architecture e.g. (x86, x64).