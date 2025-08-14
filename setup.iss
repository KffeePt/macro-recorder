; This is an Inno Setup script for creating a Windows installer.
; It is currently commented out as it is not being used.
;
; #define MyAppName "My C++ Application"
; #define MyAppVersion "1.0"
; #define MyAppPublisher "My Company, Inc."
; #define MyAppURL "https://www.example.com/"
; #define MyAppExeName "macroapp.exe"
; #define MyAssetFileName "MacroApp_Installer.zip"
;
; #include "idp.iss"
;
; [Setup]
; AppName={#MyAppName}
; AppVersion={#MyAppVersion}
; AppPublisher={#MyAppPublisher}
; AppPublisherURL={#MyAppURL}
; AppSupportURL={#MyAppURL}
; AppUpdatesURL={#MyAppURL}
; DefaultDirName={autopf}\{#MyAppName}
; DefaultGroupName={#MyAppName}
; OutputBaseFilename=setup
; WizardStyle=modern
;
; [Files]
; Source: "7za.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall
; Source: "IDP.dll"; DestDir: "{tmp}"; Flags: deleteafterinstall
;
; [Icons]
; Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
; Name: "{group}\Uninstall {#MyAppName}"; Filename: "{uninstallexe}"
;
; [Code]
; procedure InitializeWizard();
; var
;   DownloadURL: String;
; begin
;   DownloadURL := ExpandConstant('{param:DownloadURL}');
;   idpAddFile(DownloadURL, ExpandConstant('{tmp}\{#MyAssetFileName}'));
;   idpDownloadAfter(wpReady);
; end;
;
; procedure CurStepChanged(CurStep: TSetupStep);
; var
;   ResultCode: Integer;
; begin
;   if (CurStep = ssInstall) then
;   begin
;     ExtractTemporaryFile('7za.exe');
;     Exec(ExpandConstant('{tmp}\7za.exe'), 'x "' + ExpandConstant('{tmp}\{#MyAssetFileName}') + '" -o"' + ExpandConstant('{app}') + '" -y', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);
;   end;
; end;