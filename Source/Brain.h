/*
  ==============================================================================

    Brain.h
    Created: 14 Nov 2021 10:42:56pm
    Author:  No

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
#include "Definitions/SubFixture/SubFixture.h"
#include "Definitions/Fixture/Fixture.h"
#include "Definitions/Group/Group.h"
#include "Definitions/Command/Command.h"
#include "Definitions/Cue/Cue.h"
#include "Definitions/Cuelist/Cuelist.h"
#include "Definitions/Preset/Preset.h"
#include "Definitions/Programmer/Programmer.h"
#include "Definitions/CurvePreset/CurvePreset.h"
#include "Definitions/TimingPreset/TimingPreset.h"
#include "Definitions/Effect/Effect.h"
#include "Definitions/Carousel/Carousel.h"
#include "Definitions/Mapper/Mapper.h"
#include "Definitions/RunningTask.h"
#include "Definitions/Cue/Task.h"
#include "Definitions/Layout/Layout.h"
#include "Definitions/Media/Media.h"
#include "Definitions/Stamp/Stamp.h"



class Brain :
    public Thread
{
public:
    juce_DeclareSingleton(Brain, true);
    Brain();
    ~Brain();
    void clear();
    void clearUpdates();

    HashMap<int, SubFixture*>subFixtures;
    HashMap<int, Group*>groups;
    HashMap<int, Fixture*>fixtures;
    HashMap<int, Preset*>presets;
    HashMap<int, Cuelist*>cuelists;
    HashMap<int, Programmer*>programmers;
    HashMap<int, CurvePreset*>curvePresets;
    HashMap<int, TimingPreset*>timingPresets;
    HashMap<int, Effect*>effects;
    HashMap<int, Carousel*>carousels;
    HashMap<int, Mapper*>mappers;
    HashMap<int, Layout*>layouts;
    HashMap<int, Media*>medias;
    HashMap<int, Stamp*>stamps;

    Array<Cuelist*> cuelistPoolUpdating;
    Array<Cuelist*> cuelistPoolWaiting;
    Array<SubFixtureChannel*> subFixtureChannelPoolUpdating;
    Array<SubFixtureChannel*> subFixtureChannelPoolWaiting;
    Array<Cue*> cuePoolUpdating;
    Array<Cue*> cuePoolWaiting;
    Array<Programmer*> programmerPoolUpdating;
    Array<Programmer*> programmerPoolWaiting;
    Array<Effect*> effectPoolUpdating;
    Array<Effect*> effectPoolWaiting;
    Array<Carousel*> carouselPoolUpdating;
    Array<Carousel*> carouselPoolWaiting;
    Array<Mapper*> mapperPoolUpdating;
    Array<Mapper*> mapperPoolWaiting;
    Array<Stamp*> stampPoolUpdating;
    Array<Stamp*> stampPoolWaiting;

    Array<SubFixtureChannel*> swoppableChannels;
    Array<SubFixtureChannel*> grandMasterChannels;
    Array<Cuelist*> swoppedCuelists;

    double now;
    bool loadingIsRunning = false;

    bool virtualFadersNeedUpdate = false;
    bool virtualFaderButtonsNeedUpdate = false;
    bool virtualButtonsNeedUpdate = false;
    bool encoderValuesNeedRefresh = false;
    bool cuelistGridNeedRefresh = false;
    bool carouselGridNeedRefresh = false;
    bool effectGridNeedRefresh = false;

    void run() override;
    void brainLoop();
    bool skipLoop = false;

    CriticalSection usingCollections;
    CriticalSection usingTasksCollection;
    void registerSubFixture(SubFixture* f, int id);
    void unregisterSubFixture(SubFixture* f);
    void registerFixture(Fixture* f, int id, bool swap = false);
    void unregisterFixture(Fixture* f);
    void registerGroup(Group* f, int id, bool swap = false);
    void unregisterGroup(Group* f);
    void registerPreset(Preset* p, int id, bool swap = false);
    void unregisterPreset(Preset* p);
    void registerCuelist(Cuelist* c, int id, bool swap = false);
    void unregisterCuelist(Cuelist* c);
    void registerProgrammer(Programmer* p, int id, bool swap = false);
    void unregisterProgrammer(Programmer* p);
    void registerCurvePreset(CurvePreset* p, int id, bool swap = false);
    void unregisterCurvePreset(CurvePreset* p);
    void registerTimingPreset(TimingPreset* p, int id, bool swap = false);
    void unregisterTimingPreset(TimingPreset* p);
    void registerEffect(Effect* p, int id, bool swap = false);
    void unregisterEffect(Effect* p);
    void registerCarousel(Carousel* p, int id, bool swap = false);
    void unregisterCarousel(Carousel* p);
    void registerMapper(Mapper* p, int id, bool swap = false);
    void unregisterMapper(Mapper* p);
    void registerLayout(Layout* p, int id, bool swap = false);
    void unregisterLayout(Layout* p);
    void registerMedia(Media* p, int id, bool swap = false);
    void unregisterMedia(Media* p);
    void registerStamp(Stamp* p, int id, bool swap = false);
    void unregisterStamp(Stamp* p);

    void pleaseUpdate(Cuelist* c);
    void pleaseUpdate(SubFixtureChannel* f);
    void pleaseUpdate(Cue* c);
    void pleaseUpdate(Programmer* p);
    void pleaseUpdate(Effect* f);
    void pleaseUpdate(Carousel* c);
    void pleaseUpdate(Mapper* c);
    void pleaseUpdate(Stamp* s);

    void updateAllChannels();

    void grandMasterChanged();

    //void updateChannel(SubFixtureChannel* fc);

    SubFixture* getSubFixtureById(int id);
    Fixture* getFixtureById(int id);
    Group* getGroupById(int id);
    Preset* getPresetById(int id);
    Cuelist* getCuelistById(int id);
    Programmer* getProgrammerById(int id);
    CurvePreset* getCurvePresetById(int id);
    TimingPreset* getTimingPresetById(int id);
    Effect* getEffectById(int id);
    Carousel* getCarouselById(int id);
    Mapper* getMapperById(int id);
    Layout* getLayoutById(int id);
    Media* getMediaById(int id);
    Stamp* getStampById(int id);

    void swoppedCuelist(Cuelist* c);
    void unswoppedCuelist(Cuelist* c);
    bool isSwopping = false;

    static float symPosition(int index, int nElements);

    OwnedArray<RunningTask> runningTasks;
    int currentTaskId = 0;
    int newTaskId();
    void startTask(Task* t, double startTime, int cuelistId);
    void stopTasks(int cuelistId, int taskId);

    bool pleaseClearProgrammer = false;

    void goAllLoadedCuelists();
    void killAllCuelists();
    void offAllCuelists();
    void stopAllEffects();
    void stopAllCarousels();

    void resetRandomSeed(int seed);

    void showWindow(String name);
};
