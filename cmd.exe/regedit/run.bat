@rem
@rem run as adminsitrator.
@rem

@regedit /s 01_add_key.reg
@echo Key "HKCU\Software\RegeditTest" added
@pause > nul

@regedit /s 02_add_value.reg
@echo Value "StringData" added
@pause > nul

@regedit /s 03_delete_value.reg
@echo Value "QWordData" deleted
@pause > nul

@regedit /s 04_delete_key.reg
@echo key "RegeditTest" deleted
@pause > nul
