#include "bmp.h"

GLuint LoadTextureBMP(const char * pic)
{
	double width;
	double height;

	int BytesofFile;

	GLuint Texture;
	BYTE * data;
	FILE * picfile;

	picfile = fopen(pic, "rb");
	if (picfile == NULL)
		return 0;

	BITMAPFILEHEADER MyHeaderFile;
	fread(&MyHeaderFile, sizeof(BITMAPFILEHEADER), 1, picfile);
	if (MyHeaderFile.bfType != 0x4D42)
		return 0;

	BITMAPINFOHEADER MyHeaderInfo;
	fread(&MyHeaderInfo, sizeof(BITMAPINFOHEADER), 1, picfile);

	width = MyHeaderInfo.biWidth;
	height = MyHeaderInfo.biHeight;

	BytesofFile = MyHeaderInfo.biBitCount;

	data = (BYTE *)malloc(width * height * BytesofFile);

//	cout<<"bfSize: "<<MyHeaderFile.bfSize<<endl<<"bfOffBits: "<<MyHeaderFile.bfOffBits<<endl<<"biSize: "<<MyHeaderInfo.biSize<<endl<<"biBitCount: "<<MyHeaderInfo.biBitCount<<endl;
//	system("PAUSE");
//cout<<endl;

	fseek(picfile, MyHeaderFile.bfOffBits, SEEK_SET);
	fread(data, width * height, BytesofFile, picfile);
	fclose(picfile);
	
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D,  Texture);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	BYTE tmp;
	if(BytesofFile==24)
	{
	for(int i=0;i<width*height;++i)
	 {
	 tmp=data[i*3];
	 data[i*3  ]=data[i*3+2];
	 data[i*3+2]=tmp;
	 }
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	
	if(BytesofFile==32)
	{
	for(int i=0;i<width*height;++i)
	 {
	 //tmp=data[i*4  ];data[i*4  ]=data[i*4+3];data[i*4+3]=tmp;
	 //tmp=data[i*4+1];data[i*4+1]=data[i*4+2];data[i*4+2]=tmp;
	 tmp=data[i*4  ];data[i*4  ]=data[i*4+2];data[i*4+2]=tmp;
	// tmp=data[i*4+1];data[i*4+1]=data[i*4+3];data[i*4+3]=tmp;
	 }
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	
	free(data);
	return Texture;
}

	

