import React from 'react'
import { Text, View } from 'react-native'
import SequenceComponent from '../components/SequenceComponent'

export default function SequenceScreen(){
    return (
        <View>
            <SequenceComponent />
            <SequenceComponent />
            <SequenceComponent />
            <SequenceComponent />
            <SequenceComponent />
        </View>
    )
}