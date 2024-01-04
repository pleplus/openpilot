#pragma once

#include <set>

#include "selfdrive/ui/qt/offroad/settings.h"

class FrogPilotVisualsPanel : public ListWidget {
  Q_OBJECT

public:
  explicit FrogPilotVisualsPanel(SettingsWindow *parent);

private:
  void hideEvent(QHideEvent *event);
  void hideSubToggles();
<<<<<<< HEAD
  void parentToggleClicked();
  void setDefaults();
  void updateState();
=======
  void setDefaults();
  void updateMetric();

  ButtonControl *backButton;
>>>>>>> a6055f290a26ae117815591af4efbe1dc587507c

  std::set<QString> customOnroadUIKeys;
  std::set<QString> customThemeKeys;
  std::set<QString> modelUIKeys;

  std::map<std::string, ParamControl*> toggles;

  Params params;
  Params paramsMemory{"/dev/shm/params"};

  bool isMetric = params.getBool("IsMetric");
};
