#pragma once

#include <set>

#include "selfdrive/ui/qt/offroad/settings.h"

class FrogPilotControlsPanel : public ListWidget {
  Q_OBJECT

public:
  explicit FrogPilotControlsPanel(SettingsWindow *parent);

private:
  void hideEvent(QHideEvent *event);
  void hideSubToggles();
  void parentToggleClicked();
  void setDefaults();
<<<<<<< HEAD
  void updateState();

=======
  void updateMetric();

  ButtonControl *backButton;
>>>>>>> a6055f290a26ae117815591af4efbe1dc587507c
  ButtonControl *slscPriorityButton;
  ButtonIconControl *modelSelectorButton;
  DualParamValueControl *conditionalSpeedsImperial;
  DualParamValueControl *conditionalSpeedsMetric;

  std::set<QString> conditionalExperimentalKeys;
  std::set<QString> customPersonalitiesKeys;
  std::set<QString> fireTheBabysitterKeys;
  std::set<QString> laneChangeKeys;
  std::set<QString> lateralTuneKeys;
  std::set<QString> longitudinalTuneKeys;
  std::set<QString> speedLimitControllerKeys;
  std::set<QString> visionTurnControlKeys;

  std::map<std::string, ParamControl*> toggles;

  Params params;
  Params paramsMemory{"/dev/shm/params"};

  bool isMetric = params.getBool("IsMetric");
};
