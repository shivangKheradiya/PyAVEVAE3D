# PyAVEVAE3D

PyAVEVAE3D contains Proof of Concept for Python 3 embedding into AVEVA Plant Design Products ( e.g. PDMS, E3D2.1/ 3.1, Diagrams, Engineering). These software are based on PML &amp; PML.Net.

This repository has Visual Studio Project Solution. The Solution contains 2 main projects:

- **PyAVEVAInteraction :** It contains the architectural skeleton for Python Embadding into AVEVA E3D2.1.0.3. and It invoks the either system level python or virtual enviroment python.

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

3. Copy Dll files from repository to Aveva Installation Directory.

    From : ```..\PyAVEVAE3D\SampleDlls\PyAVEVAInteraction.dll```

    To : ```%AVEVA_DESIGN_EXE%```

4. Install pyavevae3dext

    -- Method 1: using ```pip install pyavevae3dext```.
    
    -- Method 2: Build the .pyd file based on the your module dependencies and build the package. [Refer Development Documetation Section](./Documentation/Development_Enviroment.md)

5. Open RunPy form using pml command ```Show !!RunPy```. RunPy Form is used to write a test python scripts.

6. Run Python Script form the Form. And All the output from python scripts will be printed in the AVEVA console. e.g. ```print("abc")``` in python will give the output in the python console.

## More information on pyavevae3dext PiPy Package.

pyavevae3dext PiPy package has basically 3 classes.

1. COMMON:

    Common Class Instentiation,
    ```python
    c = COMMON()
    ```

    Method to know about current mdb.
    ```python
    c.mdb()
    ```

    Method to execute Savework command.
    ```python
    c.savework()
    ```

    Method to execute Getwork command.
    ```python
    c.getwork()
    ```
    Getter-Setter for ```CE```,
    ```python
    print(c.ce()) #Getter
    c.ce = "/ElementName" #Setter
    ```

2. DB:

    Db Class Instentiation,
    ```python
    d = DB()
    ```

    Method to know Attributes on current elements,
    ```python
    att = d.attributes()
    print(att)
    ```

    Method to Get Collection as List for the Element,
    ```python
    elms = d.collectAllForElement("/SITE-CABLE-AREA03")
    print(elms)
    ```

    Method to Get Collection as List for the Element,
    ```python
    elms = d.collectAllFor("PIPE BRAN", "/SITE-PIPING-AREA01 /SITE-PIPING-AREA02")
    print(elms)
    ```

    Method to Set String Attribute for Element,
    ```python
    d.SetStringAttribute("/SITE-PIPING-AREA03", "Description",  "This is test description")
    ```

    Method to Set Real Attribute for Element,
    ```python
    d.SetRealAttribute("/SITE-PIPING-AREA03", "Number", 5)
    ```

    Method to Set Bool Attribute for Element,
    ```python
    d.SetBoolAttribute("/SITE-PIPING-AREA03", "Lock", True)
    ```

3. PML:

    PML Class Instentiation,
    ```python
    p = PML()
    ```

    Method to Run the PML Command in PDMS Console,
    ```python
    p.RunInPdms("$p This Message is From Python...")
    ```

    Method to Run the PML Command in .Net Environment,
    ```python
    p.Run("/SITE-CABLE-AREA03") # /SITE-CABLE-AREA03 will be set as current element 
    ```

    To utilize the methods mentioned below, the variables in the PML Commandline must be defined as global variable.

    Run the below code in PML Commandline to define the pml global variable,
    ```
    !!AR[1] = 'A'
    !!AR[2] = 'b1'
    !!AR[3] = 'C'
    !BOOL = true
    !REAL = 5
    !STR = |Hii.. This message is From PML.|
    ```

    Method to get the Value of the PML Variable as String,
    ```python
    value = p.GetPmlString("STR")
    print(value)
    ```
    
    Method to get the Value of the PML Variable as Long,
    ```python
    value = p.GetPmlReal("REAL")
    print(value)
    ```

    Method to get the Value of the PML Variable as Bool,
    ```python
    value = p.GetPmlBool("BOOL")
    print(value)
    ```

    Method to get the Value of the PML Variable as Array/ List,
    ```python
    value = p.GetPmlArray("AR")
    print(value)
    ```

## Procedure For Setting Up Development Enviroment

Refer the [Development Documetation Section](Documentation/Development_Enviroment.md) for Detailed Procedure for setting up development environment.

## General Guideline

-- For Utilzing Python with Other AVEVA Software, Please install the Python version compatible to the AVEVA module architecture e.g. (x86, x64). and Make sure the platform architectural dependencies (Python and AVEVA Dll) for Build/ Release.

-- ```conda``` Environment as well conpatible. Make sure the ```conda``` environment platform architecture e.g. (x86, x64).