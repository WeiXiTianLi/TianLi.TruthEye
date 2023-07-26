project(TianLiTruthEye.csharp.test LANGUAGES CSharp)

set(CMAKE_CSharp_FLAGS "/langversion:latest /platform:x64")

add_executable(TianLiTruthEye.csharp.test
	Program.cs
	"../../TianLi.TruthEye/include/TianLi.TruthEye.cs"
	)
set_property(TARGET TianLiTruthEye.csharp.test PROPERTY VS_DOTNET_REFERENCES
	"Microsoft.CSharp"
	"PresentationCore"
	"PresentationFramework"
	"System"
	"System.Core"
	"System.Data"
	"System.Drawing"
	"System.Data.DataSetExtensions"
	"System.Net.Http"
	"System.Xaml"
	"System.Xml"
	"System.Xml.Linq"
	"WindowsBase")
