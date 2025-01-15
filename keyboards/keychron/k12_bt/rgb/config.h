/* Copyright 2022 Dimitris Mantzouranis <d3xter93@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define SN32F2XX_RGB_MATRIX_ROW_PINS {C6, C5, C4, C9, C8, C7, C12, C11, C10, B13, C14, C13, B14, B15, D3}

#define DIP_BT_EN (1)   // 0: Disable, 1: Enable
#define DIP_WIN_MAC (0) // 0: Windows, 1: Mac

#define ITON_BT_ENABLE_ACK
#define BLUETOOTH_MANUAL_INIT

#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0
