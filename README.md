# AI-VGP332
Projects from my AI class.

Dependencies
------------

DirectX 9:
1. [Download](http://www.microsoft.com/en-ca/download/details.aspx?id=6812) the DirectX SDK.
2. BEFORE installing the SDK, unistall both versions of "Microsoft Visual C++ 2010 Redistrubtable". There should be an "x64" and "x86" version.
3. Install the DirectX SDK.

FMOD:
[Download page](http://www.fmod.org/download/)
1. Scroll down to the section titled: "FMOD Ex Programmer’s API" and download the SDK for your platform.
2. Navigate to the "lib" directory located in the FMOD install root (ie. "C:\Program Files (x86)\FMOD Programmers API\libs").
3. Copy "fmodex.dll" to the Debug folder of your project that references the SGE library.
*If "../SGE/external/lib/FMOD/fmodex_vc.lib" is missing, copy it from "FMOD install root\api\lib".