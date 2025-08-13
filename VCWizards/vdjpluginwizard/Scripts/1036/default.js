
function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddCommonConfig(selProj, strProjectName);
		AddConfig(selProj, strProjectName);
		SetupFilters(selProj);

		var InfFile = CreateInfFile();
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		InfFile.Delete();

		selProj.Object.Save();
	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

/******************************************************************************
Description: Creates a C++ project
strProjectName: Project Name
strProjectPath: The path that the project will be created in
******************************************************************************/
function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = strProjTemplatePath + '\\default.vcxproj';

		var Solution = dte.Solution;
		//var strSolutionName = "";
		var strSolutionName = strProjectName + '.sln';
		var oCloseSolution = wizard.FindSymbol("CLOSE_SOLUTION");
		if (oCloseSolution)
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = strProjectName + '.vcxproj';
		var oTarget = wizard.FindSymbol("TARGET");
		var oWizardType = wizard.FindSymbol("WIZARD_TYPE");
		var oProj;
		if (oWizardType == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectPath + "\\" + strProjectNameWithExt);
			oProj = prjItem.SubProject;
		}
		else
		{
			oProj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		return oProj;
	}
	catch(e)
	{
		throw e;
	}
}

/******************************************************************************
Description: Adds source, include and resource filters for project folders.
The symbols contain the file extensions to be used for filtering.
oProj: Project object
******************************************************************************/
function SetupFilters(oProj)
{
    try
    {

        var L_strSource_Text = "Fichiers sources";
        var group = oProj.Object.AddFilter(L_strSource_Text);
        group.Filter = "cpp;c;cc;cxx;c++;cppm;ixx;def;odl;idl;hpj;bat;asm;asmx";
        group.UniqueIdentifier = "{4FC737F1-C7A5-4376-A066-2A32D752A2FF}";

        var L_strHeader_Text = "Fichiers d'en-tête";
        group = oProj.Object.AddFilter(L_strHeader_Text);
        group.Filter = "h;hh;hpp;hxx;h++;hm;inl;inc;ipp;xsd";
        group.UniqueIdentifier = "{93995380-89BD-4b04-88EB-625FBE52EBFB}";

        var L_strResources_Text = "Fichiers de ressources";
        group = oProj.Object.AddFilter(L_strResources_Text);
        group.Filter = "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav;mfcribbon-ms";
        group.UniqueIdentifier = "{67DA6AB6-F800-4c08-8B7A-83BB121AAD01}";
    }
    catch (e)
    {
        throw e;
    }

function AddConfig(oProj, strProjectName)
{
	try
	{
		var config = oProj.Object.Configurations('Debug');
		var outdir = config.OutputDirectory;
                var intdir = config.IntermediateDirectory;
		config.ConfigurationType = typeDynamicLibrary;
		config.UseOfMFC=useMfcStdWin;
		config.DebugSettings.Command = "c:/program files/virtualdj/virtualdj.exe";
		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.PreprocessorDefinitions = GetPlatformDefine(config)+"_DEBUG;_WINDOWS;_USRDLL";
		CLTool.UsePrecompiledHeader = pchNone;
		CLTool.RuntimeLibrary = rtMultiThreadedDebug;
		CLTool.DebugInformationFormat = debugEditAndContinue;
		CLTool.WarningLevel = WarningLevel_3;
		CLTool.Optimization = optimizeDisabled;
		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.SubSystem = subSystemWindows;
		LinkTool.ProgramDatabaseFile = "$(OutDir)/" + strProjectName + ".pdb";
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalYes;
		if(wizard.FindSymbol("PLUGIN_DSP8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\SoundEffect\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_BUFFERDSP8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\SoundEffect\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_POSITIONDSP8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\SoundEffect\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_VIDEOFX8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\VideoEffect\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_VIDEOTRANS8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\VideoTransition\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_VIDEOTRANSMULTIDECK8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\VideoTransition\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_ONLINESOURCE")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\OnlineSource$(TargetName)$(TargetExt)";
		else LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\Other\Dev\$(TargetName)$(TargetExt)";

		config = oProj.Object.Configurations('Release');
		var outdir = config.OutputDirectory;
                var intdir = config.IntermediateDirectory;
		config.ConfigurationType = typeDynamicLibrary;
		config.UseOfMFC=useMfcStdWin;
		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.PreprocessorDefinitions = GetPlatformDefine(config)+"NDEBUG;_WINDOWS;_USRDLL;";
		CLTool.UsePrecompiledHeader = pchNone;
		CLTool.RuntimeLibrary = rtMultiThreaded;
		CLTool.DebugInformationFormat = debugDisabled;
		CLTool.WarningLevel = WarningLevel_3;
		CLTool.EnableFunctionLevelLinking = true;
                CLTool.EnableIntrinsicFunctions = true;
		CLTool.Optimization = optimizeMaxSpeed;
		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.SubSystem = subSystemWindows;
		LinkTool.LinkIncremental = linkIncrementalNo;
		LinkTool.GenerateDebugInformation = false;
		if(wizard.FindSymbol("PLUGIN_DSP8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\SoundEffect\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_BUFFERDSP8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\SoundEffect\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_POSITIONDSP8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\SoundEffect\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_VIDEOFX8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\VideoEffect\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_VIDEOTRANS8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\VideoTransition\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_VIDEOTRANSMULTIDECK8")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\VideoTransition\Dev\$(TargetName)$(TargetExt)";
		else if(wizard.FindSymbol("PLUGIN_ONLINESOURCE")==1) LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\OnlineSource$(TargetName)$(TargetExt)";
		else LinkTool.OutputFile = "$(LOCALAPPDATA)\VirtualDJ\Plugins64\Other\Dev\$(TargetName)$(TargetExt)";

		// make sure the rootnamespace property is set
        	oProj.Object.RootNamespace = CreateIdentifierSafeName(strProjectName);
		
		StampWindowsTargetPlatformVersion(oProj);
	}
	catch(e)
	{
		throw e;
	}
}

function SetFileProperties(projfile, strName)
{
	return false;
}

function GetLatestWindowsSDKVersion(oProj)
{
    return oProj.Object.LatestTargetPlatformVersion;
}


function GetTargetName(strName, strProjectName)
{
	try
	{
		var strTarget = strName;
		var strSubName = strName.substr(0, 6);

		if (strSubName == "plugin")
		{
			var strNameExt = strName.substr(6);
			strTarget = strProjectName + strNameExt;
		}

		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}

/******************************************************************************
Description: Adds all the files to the project based on the
Templates.inf file.
oProj: Project object
oCollection: Folder object collection to add to
strProjectName: Project name
InfFile: Templates.inf file object
******************************************************************************/
function AddFilesToCustomProj(oProj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = oProj.ProjectItems

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

		var strTpl = '';
		var strName = '';

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != '')
			{
				strName = strTpl;
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" copiera uniquement le fichier de strTemplate dans strTarget sans rendu/ajout au projet
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
				proj.Object.AddFile(strFile);
				if(strExt==".cpp")
				{
					var projfile = oProj.Object.Files(strFile);
					if (projfile != null)
					{
						var window=projfile.Object.Open(vsViewKindPrimary);
						window.visible = true;
					}
				}
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}
