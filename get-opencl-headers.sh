#!/bin/bash
# Created by Robert Wang.
DIR=$(pwd)/include/

echo "  Start downloading from Khronous's repository:"
for VERSION in 10 11 12 20 21; do
        echo "      Downloading OpenCL headers for version ${VERSION}..."
        
        CLDIR="${DIR}/CL${VERSION}"
        if [ -d "$CLDIR" ]; then rm -rf $CLDIR; fi
        mkdir -p $CLDIR
        cd $CLDIR
        
        wget -q https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl.h \
                https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl_d3d10.h \
                https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl_ext.h \
                https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl_gl.h \
                https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl_gl_ext.h \
                https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl_platform.h \
                https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/opencl.h
        
        if [ $VERSION -eq 12 ] || [ $VERSION -eq 20 ] || [ $VERSION -eq 21 ]; then        
            wget -q https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl_d3d11.h \
                    https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl_dx9_media_sharing.h \
                    https://raw.githubusercontent.com/KhronosGroup/OpenCL-Headers/opencl${VERSION}/cl_egl.h
        fi        
        
        
        if [ -n "$1" ] && [ $1 = "--include-clhpp" ]; then 
            if [ $VERSION -eq 10 ] || [ $VERSION -eq 11 ] || [ $VERSION -eq 12 ]; then    
                wget -q https://raw.githubusercontent.com/KhronosGroup/OpenCL-CLHPP/master/input_cl.hpp \
                        https://raw.githubusercontent.com/KhronosGroup/OpenCL-CLHPP/master/gen_cl_hpp.py
                python gen_cl_hpp.py
                rm input_cl.hpp
                rm gen_cl_hpp.py
            fi
            
            if [ $VERSION -eq 20 ] || [ $VERSION -eq 21 ]; then       
                wget -q https://raw.githubusercontent.com/KhronosGroup/OpenCL-CLHPP/master/input_cl2.hpp
                mv input_cl2.hpp cl2.hpp
            fi
        fi 
done

echo "  Linking default CL folder to OpenCL 1.2..." 
cd "${DIR}"
if [ -d "CL" ]; then rm CL; fi
ln -s CL12 CL
echo "  Done!"; echo " ";
