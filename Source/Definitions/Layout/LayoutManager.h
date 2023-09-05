/*
  ==============================================================================

    ObjectManager.h
    Created: 26 Sep 2020 10:02:28am
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "Layout.h"

class LayoutManager :
    public BaseManager<Layout>
    // public Layout::ObjectListener,
    //public URL::DownloadTask::Listener
{
public:
    juce_DeclareSingleton(LayoutManager, true);

    LayoutManager();
    ~LayoutManager();

    // Factory<Object> factory;

    // BoolParameter* blackOut;

    //ui
    // IntParameter* gridThumbSize;
    // FloatParameter* defaultFlashValue;
    // BoolParameter* filterActiveInScene;
    // BoolParameter* lockUI;

    // URL downloadURL;
    // std::unique_ptr<URL::DownloadTask> downloadTask;
     
    // void downloadObjects();
    // void updateFactoryDefinitions();
    void addItemInternal(Layout* o, var data) override;
    void removeItemInternal(Layout* o) override;

    // int getFirstAvailableObjectID(Object* excludeObject = nullptr);
    // Object* getObjectWithID(int id, Object* excludeObject = nullptr);

    // void objectIDChanged(Object* o, int previousID) override;

    void onContainerParameterChanged(Parameter* p) override;

    // var getSceneData();
    // void updateSceneData(var& sceneData);
    // void lerpFromSceneData(var startData, var endData, float weight);

    // virtual void progress(URL::DownloadTask* task, int64 downloaded, int64 total) override;
    // virtual void finished(URL::DownloadTask* task, bool success) override;

};