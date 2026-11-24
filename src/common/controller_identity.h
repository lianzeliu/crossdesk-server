/*
 * @Author: DI JUNKUN
 * @Date: 2026-10-30
 * Copyright (c) 2026 by DI JUNKUN, All Rights Reserved.
 */

#ifndef _CONTROLLER_IDENTITY_H_
#define _CONTROLLER_IDENTITY_H_

#include <string>

inline bool IsTemporaryControllerRegistration(const std::string& id) {
  return id == "web" || id == "cli";
}

inline bool IsTemporaryControllerId(const std::string& id) {
  return id.rfind("web-", 0) == 0 || id.rfind("cli-", 0) == 0;
}

// A user-chosen device ID: 1-9 letters or digits, first character not '0'.
// "C-", "web-" and "cli-" prefixes are reserved for controller/temporary
// identities, as are the bare "web"/"cli" registration kinds. The '-' in
// those prefixes can never appear here (only letters/digits are allowed),
// but the check is kept explicit so the reservation survives any later
// relaxation of the character set.
inline bool ValidCustomDeviceId(const std::string& id) {
  if (id.empty() || id.size() > 9 || id[0] == '0') return false;
  for (char c : id) {
    const bool digit = c >= '0' && c <= '9';
    const bool upper = c >= 'A' && c <= 'Z';
    const bool lower = c >= 'a' && c <= 'z';
    if (!digit && !upper && !lower) return false;
  }
  if (id.rfind("C-", 0) == 0 || id.rfind("web-", 0) == 0 ||
      id.rfind("cli-", 0) == 0)
    return false;
  if (id == "web" || id == "cli") return false;
  return true;
}

#endif
