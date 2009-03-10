/* Cuberok
 * Copyright (C) 2008-2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "style.h"

Q_EXPORT_PLUGIN2(cuberok_style, StylePlugin) 

StylePlugin::StylePlugin()
{
}

QStringList StylePlugin::keys() const
{
	QStringList l;
	l << "Cuberok";
	return l;
}

QStyle *StylePlugin::create(const QString &key)
{
	//if(key == "Cuberok")
		return new CuberokStyle();
		//else
		//return 0;
}


CuberokStyle::CuberokStyle()
{
}

int CuberokStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    int ret = -1;
    switch (metric) {
    case PM_ButtonDefaultIndicator:
        ret = 0;
        break;
    case PM_ButtonShiftHorizontal:
    case PM_ButtonShiftVertical:
        ret = 0;
        break;
    case PM_MessageBoxIconSize:
        ret = 48;
        break;
    case PM_ListViewIconSize:
        ret = 32;
        break;
    case PM_DialogButtonsSeparator:
    case PM_SplitterWidth:
        ret = 6;
        break;
    case PM_ScrollBarSliderMin:
        ret = 26;
        break;
    case PM_MenuPanelWidth: //menu framewidth
        ret = 2;
        break;
    case PM_TitleBarHeight:
        ret = 24;
        break;
    case PM_ScrollBarExtent:
        ret = 15;
        break;
    case PM_SliderThickness:
        ret = 15;
        break;
    case PM_SliderLength:
        ret = 27;
        break;
    case PM_DockWidgetTitleMargin:
        ret = 1;
        break;
    case PM_MenuBarVMargin:
        ret = 1;
        break;
    case PM_DefaultFrameWidth:
        ret = 2;
        break;
    case PM_SpinBoxFrameWidth:
        ret = 3;
        break;
    case PM_MenuBarItemSpacing:
        ret = 6;
    case PM_MenuBarHMargin:
        ret = 0;
        break;
    case PM_ToolBarHandleExtent:
        ret = 9;
        break;
    case PM_ToolBarItemSpacing:
        ret = 2;
        break;
    case PM_ToolBarFrameWidth:
        ret = 0;
        break;
    case PM_ToolBarItemMargin:
        ret = 1;
        break;
    case PM_ToolBarIconSize:
        ret = 32;
        break;
    case PM_ButtonMargin:
        ret = 6;
        break;
    case PM_SmallIconSize:
        ret = 16;
        break;
    case PM_ButtonIconSize:
        ret = 24;
        break;
    case PM_MenuVMargin:
    case PM_MenuHMargin:
        ret = 0;
        break;
    case PM_DockWidgetTitleBarButtonMargin:
        ret = 4;
        break;
    case PM_MaximumDragDistance:
        return -1;
    case PM_TabCloseIndicatorWidth:
    case PM_TabCloseIndicatorHeight:
        return 20;
    default:
        break;
    }

    return ret != -1 ? ret : QWindowsStyle::pixelMetric(metric, option, widget);
}
