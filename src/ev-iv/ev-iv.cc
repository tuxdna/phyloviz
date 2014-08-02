#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSeparator.h>

int
main(int argc, char ** argv)
{
  // Initializes SoQt library (and implicitly also the Coin and Qt
  // libraries). Returns a top-level / shell Qt window to use.
  QWidget * mainwin = SoQt::init(argc, argv, argv[0]);

  char fname[265]="camera.iv";
  if(argc>1)
  {
	  strcpy(fname,argv[1]);
  }

  // Make a dead simple scene graph by using the Coin library, only
  // containing a single yellow cone under the scenegraph root.
  SoSeparator * root = new SoSeparator;
  root->ref();

   SoInput myInput;
   if (! myInput.openFile(fname)) 
      return 1;
   SoSeparator *fileContents = SoDB::readAll(&myInput);
   if (fileContents == NULL) 
      return 1;

  root->addChild(fileContents);


  // Use one of the convenient SoQt viewer classes.
  SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(mainwin);
  eviewer->setSceneGraph(root);
  eviewer->show();

  // Pop up the main window.
  SoQt::show(mainwin);
  // Loop until exit.
  SoQt::mainLoop();

  // Clean up resources.
  delete eviewer;
  root->unref();

  return 0;
}
