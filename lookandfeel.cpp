#include "lookandfeel.h"

extern QString style_name;

LookAndFeel::LookAndFeel(QWidget *parent)
    : QDialog(parent), _style(0), _role(0), _group(0)
{
	ui.setupUi(this);
	
	ui.comboBox_style->addItems(QStyleFactory::keys());
	for(int i=0; i<QStyleFactory::keys().count(); i++) {
		if(style_name == QStyleFactory::keys().at(i))
			ui.comboBox_style->setCurrentIndex(i);
	}
	
	ui.comboBox_group->addItem("Active");
	ui.comboBox_group->addItem("Disabled");
	ui.comboBox_group->addItem("Inactive");
	
	ui.comboBox_role->addItem("WindowText");
	ui.comboBox_role->addItem("Button");
	ui.comboBox_role->addItem("Light");
	ui.comboBox_role->addItem("Midlight");
	ui.comboBox_role->addItem("Dark");
	ui.comboBox_role->addItem("Mid");
	ui.comboBox_role->addItem("Text");
	ui.comboBox_role->addItem("BrightText");
	ui.comboBox_role->addItem("ButtonText");
	ui.comboBox_role->addItem("Base");
	ui.comboBox_role->addItem("Window");
	ui.comboBox_role->addItem("Shadow");
	ui.comboBox_role->addItem("Highlight");
	ui.comboBox_role->addItem("HighlightedText");
	
	ui.comboBox_brush->addItem("NoBrush");
	ui.comboBox_brush->addItem("SolidPattern");
	ui.comboBox_brush->addItem("Dense1Pattern");
	ui.comboBox_brush->addItem("Dense2Pattern");
	ui.comboBox_brush->addItem("Dense3Pattern");
	ui.comboBox_brush->addItem("Dense4Pattern");
	ui.comboBox_brush->addItem("Dense5Pattern");
	ui.comboBox_brush->addItem("Dense6Pattern");
	ui.comboBox_brush->addItem("Dense7Pattern");
	ui.comboBox_brush->addItem("HorPattern");
	ui.comboBox_brush->addItem("VerPattern");
	ui.comboBox_brush->addItem("CrossPattern");
	ui.comboBox_brush->addItem("BDiagPattern");
	ui.comboBox_brush->addItem("FDiagPattern");
	ui.comboBox_brush->addItem("DiagCrossPattern");
	//ui.comboBox_brush->addItem("LinearGradientPattern");
	//ui.comboBox_brush->addItem("RadialGradientPattern");
	//ui.comboBox_brush->addItem("ConicalGradientPattern");

	QBrush br = _palette.brush((QPalette::ColorGroup)_group, (QPalette::ColorRole)_role);
	ui.comboBox_brush->setCurrentIndex(br.style());
	QPalette p(br.color());
	ui.pushButton_color->setPalette(p);
}

LookAndFeel::~LookAndFeel()
{

}

void LookAndFeel::applyAll()
{
	QApplication::setStyle(ui.frame->style());
	QApplication::setPalette(ui.frame->palette());
}

void LookAndFeel::set_style(QString st)
{
	style_name = st;
	_style = QStyleFactory::create(st);
	previewStyle(_style);
}

void LookAndFeel::previewStyle(QStyle * style)
{
	//setStyleRecursive(style, ui.frame);
	setStyleRecursive(style, this);
}

void LookAndFeel::setStyleRecursive(QStyle *style, QWidget *wid)
{
	if(!wid) return;
	wid->setStyle(style);
	foreach(QObject *o, wid->children()) {
		setStyleRecursive(style, qobject_cast<QWidget*>(o));
	}
}

void LookAndFeel::set_group(int i)
{
	_group = i;
	QBrush br = _palette.brush((QPalette::ColorGroup)_group, (QPalette::ColorRole)_role);
	ui.comboBox_brush->setCurrentIndex(br.style());
	QPalette p(br.color());
	ui.pushButton_color->setPalette(p);
}

void LookAndFeel::set_role(int i)
{
	_role = i;
	QBrush br = _palette.brush((QPalette::ColorGroup)_group, (QPalette::ColorRole)_role);
	ui.comboBox_brush->setCurrentIndex(br.style());
	QPalette p(br.color());
	ui.pushButton_color->setPalette(p);
}

void LookAndFeel::set_brush(int i)
{
	//QBrush br = _palette.brush((QPalette::ColorGroup)_group, (QPalette::ColorRole)_role);
	QColor c = ui.pushButton_color->palette().brush(QPalette::Active, QPalette::Window).color();
	QBrush br2(c, (Qt::BrushStyle)i);
	_palette.setBrush((QPalette::ColorGroup)_group, (QPalette::ColorRole)_role, br2);
	previewPalette(_palette);
}

void LookAndFeel::set_color()
{
	QBrush br = _palette.brush((QPalette::ColorGroup)_group, (QPalette::ColorRole)_role);
	QBrush br2(QColorDialog::getColor(br.color()), br.style());
	_palette.setBrush((QPalette::ColorGroup)_group, (QPalette::ColorRole)_role, br2);
	QPalette p(br2.color());
	previewPalette(_palette);
	ui.pushButton_color->setPalette(p);
}

void LookAndFeel::previewPalette(QPalette &palette)
{
	//setPaletteRecursive(palette, ui.frame);
	setPaletteRecursive(palette, this);
}

void LookAndFeel::setPaletteRecursive(QPalette &palette, QWidget *wid)
{
	if(!wid) return;
	wid->setPalette(palette);
	foreach(QObject *o, wid->children()) {
		setPaletteRecursive(palette, qobject_cast<QWidget*>(o));
	}
}

void LookAndFeel::acceptWithApply()
{
	applyAll();
	accept();
}

void LookAndFeel::quick()
{
	QColor c1 = QColorDialog::getColor(_palette.brush(QPalette::Active, QPalette::Button).color());
	QColor c2 = QColorDialog::getColor(_palette.brush(QPalette::Active, QPalette::Window).color());
	QPalette p(c1, c2);
	//QPalette p2 = QApplication::palette(); // HACK
	//QApplication::setPalette(p);
	//p = QApplication::palette();
	//QApplication::setPalette(p2);
	_palette = p;
	previewPalette(_palette);
}