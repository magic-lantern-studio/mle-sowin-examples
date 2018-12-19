// COPYFIRHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  For information concerning this header file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// Include Open Inventor header files.
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCone.h>

SoSeparator *
readFile(const char *filename)
{
   // Open the input file.
   SoInput sceneInput;
   if (! sceneInput.openFile(filename)) {
      fprintf(stderr, "Cannot open file %s.\n", filename);
      return NULL;
   }

   // Read the whole file into the database.
   SoSeparator *root = SoDB::readAll(&sceneInput);
   if (root == NULL) {
      fprintf(stderr, "Problem reading file.\n");
      return NULL;
   } 

   sceneInput.closeFile();
   return root;
}

int
main(int, char ** argv)
{
	// Initialize SoWin (and implicitly Coin). This will return a top-level, shell window to use.
    HWND window = SoWin::init(argv[0]);
    if (window == NULL) exit(1);

	// Create a viewer.
    SoWinExaminerViewer * viewer = new SoWinExaminerViewer(window);

	// The scenegraph is going to consist of the data and node hierarchy defined by the Open Inventor file, teapot.iv.
	// To avoid that the root object gets deleted (because its reference counter is 0), call ref() on the root node.
    SoSeparator * root = readFile("../media/teapot.iv");
	if (root == NULL) {
		delete viewer;
		exit(1);
	}
	root->ref();

	// Tell the viewer to render the scenegraph (which is represented through the root node).
    viewer->setSceneGraph(root);
    viewer->show();

	// Tell SoWin to show the window and run in a loop.
    SoWin::show(window);
    SoWin::mainLoop();

	// When the application is terminated, the viewer is deleted and call unref() on the root node.
    delete viewer;
    root->unref();
    return 0;
}
