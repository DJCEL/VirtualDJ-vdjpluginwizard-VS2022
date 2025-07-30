
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

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		strProjTemplate = strProjTemplatePath + '\\default.vcxproj';

		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.vcxproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{
		var config = proj.Object.Configurations('Debug');
		config.ConfigurationType = typeDynamicLibrary;
		config.UseOfMFC=useMfcStdWin;
		config.DebugSettings.Command = "c:/program files/virtualdj/virtualdj.exe";
		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.PreprocessorDefinitions = GetPlatformDefine(config)+"_DEBUG;_WINDOWS;_USRDLL";
		CLTool.UsePrecompiledHeader = pchNone;
		CLTool.RuntimeLibrary = rtMultiThreadedDebug;
		CLTool.DebugInformationFormat = debugEditAndContinue;
		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.ProgramDatabaseFile = "$(OutDir)/" + strProjectName + ".pdb";
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalYes;
		if(wizard.FindSymbol("PLUGIN_DSP8")==1) LinkTool.OutputFile = "$(OutDir)/VirtualDJ/Plugins/SoundEffect/debug_" + strProjectName + ".dll";
		else if(wizard.FindSymbol("PLUGIN_VIDEOFX8")==1) LinkTool.OutputFile = "$(OutDir)/VirtualDJ/Plugins/VideoEffect/debug_" + strProjectName + ".dll";
		else if(wizard.FindSymbol("PLUGIN_VIDEOTRANS8")==1) LinkTool.OutputFile = "$(OutDir)/VirtualDJ/Plugins/VideoTransition/debug_" + strProjectName + ".dll";
		else LinkTool.OutputFile = "$(OutDir)/VirtualDJ/Plugins/debug_" + strProjectName + ".dll";

		config = proj.Object.Configurations('Release');
		config.ConfigurationType = typeDynamicLibrary;
		config.UseOfMFC=useMfcStdWin;
		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.PreprocessorDefinitions = GetPlatformDefine(config)+"NDEBUG;_WINDOWS;_USRDLL;";
		CLTool.UsePrecompiledHeader = pchNone;
		CLTool.RuntimeLibrary = rtMultiThreaded;
		CLTool.DebugInformationFormat = debugDisabled;
		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.LinkIncremental = linkIncrementalNo;
		LinkTool.GenerateDebugInformation = false;
		LinkTool.OutputFile = "$(OutDir)/" + strProjectName + ".dll";
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

function GetTargetName(strName, strProjectName)
{
	try
	{
		var strTarget = strName;

		if (strName.substr(0, 6) == "plugin")
		{
			strTarget = strProjectName + strName.substr(6);
		}

		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems

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
					var projfile = proj.Object.Files(strFile);
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
